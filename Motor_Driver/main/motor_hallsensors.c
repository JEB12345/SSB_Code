#include "motor_state.h"
#include "motor_hallsensors.h"
#include "p33Exxxx.h"
#include "motor_pindefs.h"
#include "motor_led.h"
hallsensor_data hallsensor_state;
extern motor_data motor_state;

return_value_t hallsensors_init() {
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

    return hallsensor_state.init_return;
}

void __attribute__((__interrupt__, no_auto_psv)) _IC1Interrupt(void) {
    hallsensor_state.prev_state = hallsensor_state.cur_state;
    hallsensor_state.cur_state = (HALL1<<2)|(HALL2<<1)|HALL3;
    if(hallsensor_state.prev_state==0b001 && hallsensor_state.cur_state == 0b101){
        //index increases
        ++motor_state.rotor_turns;
    } else if (hallsensor_state.cur_state==0b001 && hallsensor_state.prev_state == 0b101){
        //index decreases
        --motor_state.rotor_turns;
    }
    
    IFS0bits.IC1IF = 0; // Reset respective interrupt flag
}

void __attribute__((__interrupt__, no_auto_psv)) _IC2Interrupt(void) {
    hallsensor_state.prev_state = hallsensor_state.cur_state;
    hallsensor_state.cur_state = (HALL1<<2)|(HALL2<<1)|HALL3;
    if(hallsensor_state.prev_state==0b001 && hallsensor_state.cur_state == 0b101){
        //index increases
        ++motor_state.rotor_turns;
    } else if (hallsensor_state.cur_state==0b001 && hallsensor_state.prev_state == 0b101){
        //index decreases
        --motor_state.rotor_turns;
    }

    IFS0bits.IC2IF = 0; // Reset respective interrupt flag
}

void __attribute__((__interrupt__, no_auto_psv)) _IC3Interrupt(void) {
    hallsensor_state.prev_state = hallsensor_state.cur_state;
    hallsensor_state.cur_state = (HALL1<<2)|(HALL2<<1)|HALL3;
    if(hallsensor_state.prev_state==0b001 && hallsensor_state.cur_state == 0b101){
        //index increases
        ++motor_state.rotor_turns;
    } else if (hallsensor_state.cur_state==0b001 && hallsensor_state.prev_state == 0b101){
        //index decreases
        --motor_state.rotor_turns;
    }
    IFS2bits.IC3IF = 0; // Reset respective interrupt flag
}