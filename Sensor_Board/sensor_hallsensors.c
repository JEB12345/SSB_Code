#include "sensor_state.h"
#include "sensor_hallsensors.h"
#include "p33Exxxx.h"
#include "sensor_pindefs.h"
#include "sensor_led.h"
hallsensor_data hallsensor_state;
extern motor_data motor_state;

float hallsensors_state_transitions[8][8];
unsigned hallsensors_state_valid_transitions[8][8];
unsigned hallsensors_state_direction[8][8];

return_value_t hallsensors_init() {
    unsigned i,j;
    hallsensor_state.init_return = RET_OK;
    hallsensor_state.cur_state = 0b000;
    hallsensor_state.prev_state = 0b000;
    //set up IOC stuff
    //IC1CON1bits.ICTSEL = 0b000; //we don't care about the timer for now
    IC1CON1bits.ICM = 0b001; //interrupt on falling or rising edge
    IC1CON2bits.TRIGSTAT = 0;
    IFS0bits.IC1IF = 0; // Clear the IC1 interrupt status flag
    IEC0bits.IC1IE = 1; // Enable IC1 interrupts

    IC2CON1bits.ICM = 0b001; //interrupt on falling or rising edge
    IC2CON2bits.TRIGSTAT = 0;
    IFS0bits.IC2IF = 0; // Clear the IC1 interrupt status flag
    IEC0bits.IC2IE = 1; // Enable IC1 interrupts

    IC3CON1bits.ICM = 0b001; //interrupt on falling or rising edge
    IC3CON2bits.TRIGSTAT = 0;
    IFS2bits.IC3IF = 0; // Clear the IC1 interrupt status flag
    IEC2bits.IC3IE = 1; // Enable IC1 interrupts

    hallsensors_state_transitions[0b001][0b101] = 0.;
    hallsensors_state_transitions[0b101][0b100] = 60.;
    hallsensors_state_transitions[0b100][0b110] = 120.;
    hallsensors_state_transitions[0b110][0b010] = 180.;
    hallsensors_state_transitions[0b010][0b011] = 240.;
    hallsensors_state_transitions[0b011][0b001] = 300.;
    hallsensors_state_transitions[0b101][0b001] = 0.;
    hallsensors_state_transitions[0b100][0b101] = 60.;
    hallsensors_state_transitions[0b110][0b100] = 120.;
    hallsensors_state_transitions[0b010][0b110] = 180.;
    hallsensors_state_transitions[0b011][0b010] = 240.;
    hallsensors_state_transitions[0b001][0b011] = 300.;
    for(i=0;i<8;++i){
        for(j=0;j<8;++j){
            hallsensors_state_transitions[i][j] *= 3.141592/180.;
        }
    }

    for(i=0;i<8;++i){
        for(j=0;j<8;++j){
            hallsensors_state_valid_transitions[i][j] = 0;
        }
    }
    hallsensors_state_valid_transitions[0b001][0b101] = 1;
    hallsensors_state_valid_transitions[0b101][0b100] = 1;
    hallsensors_state_valid_transitions[0b100][0b110] = 1;
    hallsensors_state_valid_transitions[0b110][0b010] = 1;
    hallsensors_state_valid_transitions[0b010][0b011] = 1;
    hallsensors_state_valid_transitions[0b011][0b001] = 1;
    hallsensors_state_valid_transitions[0b101][0b001] = 1;
    hallsensors_state_valid_transitions[0b100][0b101] = 1;
    hallsensors_state_valid_transitions[0b110][0b100] = 1;
    hallsensors_state_valid_transitions[0b010][0b110] = 1;
    hallsensors_state_valid_transitions[0b011][0b010] = 1;
    hallsensors_state_valid_transitions[0b001][0b011] = 1;

    for(i=0; i<8;++i){
        hallsensors_state_valid_transitions[0][i] = 1;
    }

    for(i=0;i<8;++i){
        for(j=0;j<8;++j){
            hallsensors_state_direction[i][j] = 0;
        }
    }

    hallsensors_state_direction[0b001][0b101] = 1;
    hallsensors_state_direction[0b101][0b100] = 1;
    hallsensors_state_direction[0b100][0b110] = 1;
    hallsensors_state_direction[0b110][0b010] = 1;
    hallsensors_state_direction[0b010][0b011] = 1;
    hallsensors_state_direction[0b011][0b001] = 1;
    hallsensors_state_direction[0b101][0b001] = 2;
    hallsensors_state_direction[0b100][0b101] = 2;
    hallsensors_state_direction[0b110][0b100] = 2;
    hallsensors_state_direction[0b010][0b110] = 2;
    hallsensors_state_direction[0b011][0b010] = 2;
    hallsensors_state_direction[0b001][0b011] = 2;

    //set up a free running timer: TIMER 5
    T5CONbits.TON = 0; 		// Disable Timer
    T5CONbits.TCS = 0; 		// Select internal instruction cycle clock
    T5CONbits.TGATE = 0; 	// Disable Gated Timer mode
    T5CONbits.TCKPS = 2;        // prescaler: 1:64 ==  914.3e-9s
    PR5 = 0xFFFF; 
    TMR5 = 0x00; 			// Clear timer register
    IFS1bits.T5IF = 0; 		// Clear Timer5 Interrupt Flag
    IEC1bits.T5IE = 1; 		// Enable Timer5 interrupt (detect motor not moving)
    T5CONbits.TON = 1; 		// Start Timer

    return hallsensor_state.init_return;
}

void __attribute__((__interrupt__, no_auto_psv)) _T5Interrupt(void)
{
    hallsensor_state.direction = 0;
    IFS1bits.T5IF = 0; // Clear Timer 1 Interrupt Flag
}


void hallsensors_interpolate()
{
    float timestep = 914.3; //ns/tick
    float timediff = hallsensor_state.last_update_tmr;
    float newtimediff = TMR5;
    float anglediff = 2*3.141592/6;
    float anglemoved = ((1.*newtimediff)/timediff)*anglediff;
    if(anglemoved > anglediff){
        anglemoved = anglediff;
    } else if(anglemoved<0){
        anglemoved = 0;
    }

    switch(hallsensor_state.direction){
        case 1: //positive direction
            motor_state.rotor_state_interpolated = motor_state.rotor_state+anglemoved;
            motor_state.rotor_speed = 1e9/(timediff*timestep);
            
            break;
        case 2: //negative direction
            motor_state.rotor_state_interpolated = motor_state.rotor_state-anglemoved;
            motor_state.rotor_speed = 1e9/(timediff*timestep);
            break;
        default:
            motor_state.rotor_state_interpolated = motor_state.rotor_state;
            motor_state.rotor_speed = 0.;
            break; //not moving, copy value of nearest hall sensor
    }
}

void __attribute__((__interrupt__, no_auto_psv)) _IC1Interrupt(void) {
    uint8_t tmp = (HALL1<<2)|(HALL2<<1)|HALL3;
    uint8_t cur = hallsensor_state.cur_state;
    uint8_t prev = hallsensor_state.prev_state;
    uint8_t tmp2 = hallsensors_state_valid_transitions[cur][tmp];
    if(tmp2&& cur!=tmp){
        hallsensor_state.prev_state = cur;
        hallsensor_state.cur_state = tmp;
        motor_state.rotor_state = hallsensors_state_transitions[cur][tmp];
        hallsensor_state.direction = hallsensors_state_direction[cur][tmp];
        hallsensor_state.last_update_tmr = TMR5;
        TMR5 = 0;
        if(cur==0b001 && tmp == 0b101){
            //index increases
            ++motor_state.rotor_turns;
        } else if (tmp==0b001 && cur == 0b101){
            //index decreases
            --motor_state.rotor_turns;
        }
    }

    IFS0bits.IC1IF = 0; // Reset respective interrupt flag
}

void __attribute__((__interrupt__, no_auto_psv)) _IC2Interrupt(void) {
    uint8_t tmp = (HALL1<<2)|(HALL2<<1)|HALL3;
    uint8_t cur = hallsensor_state.cur_state;
    uint8_t prev = hallsensor_state.prev_state;
    uint8_t tmp2 = hallsensors_state_valid_transitions[cur][tmp];
    if(tmp2&& cur!=tmp){
        hallsensor_state.prev_state = cur;
        hallsensor_state.cur_state = tmp;
        motor_state.rotor_state = hallsensors_state_transitions[cur][tmp];
        hallsensor_state.direction = hallsensors_state_direction[cur][tmp];
        hallsensor_state.last_update_tmr = TMR5;
        TMR5 = 0;
    }

    IFS0bits.IC2IF = 0; // Reset respective interrupt flag
}

void __attribute__((__interrupt__, no_auto_psv)) _IC3Interrupt(void) {
    uint8_t tmp = (HALL1<<2)|(HALL2<<1)|HALL3;
    uint8_t cur = hallsensor_state.cur_state;
    uint8_t prev = hallsensor_state.prev_state;
    uint8_t tmp2 = hallsensors_state_valid_transitions[cur][tmp];
    if(tmp2&& cur!=tmp){
        hallsensor_state.prev_state = cur;
        hallsensor_state.cur_state = tmp;
        hallsensor_state.direction = hallsensors_state_direction[cur][tmp];
        hallsensor_state.last_update_tmr = TMR5;
        TMR5 = 0;
        motor_state.rotor_state = hallsensors_state_transitions[cur][tmp];
    }
    IFS2bits.IC3IF = 0; // Reset respective interrupt flag
}