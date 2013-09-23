#include "p33Exxxx.h"
#include "sensor_pindefs.h"
#include "sensor_state.h"
#ifdef DOMOTOR
#include "sensor_pmsm.h"
#include "math.h"
//#include "../../CAD/Electronics/Motor_Board/PMSM/Code/PMSM.h"
#include "../../PMSM/Code/PMSM.h" 
motor_data  motor_state;
MotorInfo motor_info;
#define PIC_MC

#ifndef PIC_MC
volatile uint16_t t2_ontime, t2_offtime;
volatile uint16_t t3_ontime, t3_offtime;
volatile uint16_t t4_ontime, t4_offtime;
#endif

return_value_t pmsm_init()
{
    EN_GATE = 0;
    motor_state.rotor_position = 0x0;
    motor_state.rotor_turns = 0x1FFF;

#ifdef PIC_MC
    //set up PWM
    PTCONbits.PTEN = 0;
    PTPER = 4096; //4096*7.14ns = approx 34kHz
    PTCON2bits.PCLKDIV = 0b000; //prescaler 1:1
    PWMLOCK_OFF;
    PWMCON1 = 0x0;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    IOCON1 = 0x0;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    FCLCON1 = 0x0;
    ALTDTR1 = 0xFFFF;
    ALTDTR2 = 0xFFFF;
    ALTDTR3 = 0xFFFF;
    PWMCON2 = 0x0;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    IOCON2 = 0x0;
    PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    FCLCON2 = 0x0;


    PWMCON3 = 0x0;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    IOCON3 = 0x0;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    FCLCON3 = 0x0;

    //PWM1

    PWMCON1bits.FLTIEN = 0;
    PWMCON1bits.CLIEN = 0;
    PWMCON1bits.TRGIEN = 0;
    PWMCON1bits.DTC=0b10;
    PWMCON1bits.ITB = 0; //master time base
    PWMCON1bits.MDCS = 0; //independent period
    IFS5bits.PWM1IF = 0;
    PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    IOCON1bits.PENH = 1;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    IOCON1bits.PENL = 0; // only the PWMH pin is controlled
    PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    FCLCON1bits.FLTMOD = 0b11; //disable fault input
    PHASE1 = 0;
    PDC1 = 0;

    //PWM2
    PWMCON2bits.FLTIEN = 0;
    PWMCON2bits.DTC=0b10;
    PWMCON2bits.CLIEN = 0;
    PWMCON2bits.TRGIEN = 0;
    PWMCON2bits.ITB = 0; //master time base
    PWMCON2bits.MDCS = 0; //independent period
    IFS5bits.PWM2IF = 0;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    IOCON2bits.PENH = 1;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    IOCON2bits.PENL = 0; // only the PWMH pin is controlled
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    FCLCON2bits.FLTMOD = 0b11; //disable fault input
    PHASE2 = 0;
    PDC2 = 0;

    //PWM3
    PWMCON3bits.FLTIEN = 0;
    PWMCON3bits.DTC=0b10;
    PWMCON3bits.CLIEN = 0;
    PWMCON3bits.TRGIEN = 0;
    PWMCON3bits.ITB = 0; //master time base
    PWMCON3bits.MDCS = 0; //independent period
    IFS6bits.PWM3IF = 0;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    IOCON3bits.PENH = 1;
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    IOCON3bits.PENL = 0; // only the PWMH pin is controlled
     PWMKEY = 0XABCD;
    PWMKEY = 0x4321;
    FCLCON3bits.FLTMOD = 0b11; //disable fault input
    PHASE3 = 0;
    PDC3 = 0;

    PTCONbits.PTEN = 1;
#else
    //set up timer 2/3/4 for pwm 1, 2 and 3
    T2CONbits.TON = 0; 		// Disable Timer
    T2CONbits.TCS = 0; 		// Select internal instruction cycle clock
    T2CONbits.TGATE = 0; 	// Disable Gated Timer mode
    T2CONbits.TCKPS = 1;        // prescaler: 1/8
    PR2 = 4096; //4096*8 = 0.233ms
    TMR2 = 0x00; 			// Clear timer register
    IPC1bits.T2IP = 0x01; 		// Set Timer1 Interrupt Priority Level to 6 = very high priority
    IFS0bits.T2IF = 0; 		// Clear Timer1 Interrupt Flag
    IEC0bits.T2IE = 0; 		// Enable Timer1 interrupt
    T2CONbits.T32 = 0;          //independent 16 bit timer
    T2CONbits.TON = 1; 		// Start Timer

    T3CONbits.TON = 0; 		// Disable Timer
    T3CONbits.TCS = 0; 		// Select internal instruction cycle clock
    T3CONbits.TGATE = 0; 	// Disable Gated Timer mode
    T3CONbits.TCKPS = 1;        // prescaler: 1/8
    PR3 = 4096; //4096*8 = 0.233ms
    TMR3 = 0x00; 			// Clear timer register
    IPC2bits.T3IP = 0x01; 		// Set Timer1 Interrupt Priority Level to 6 = very high priority
    IFS0bits.T3IF = 0; 		// Clear Timer1 Interrupt Flag
    IEC0bits.T3IE = 0; 		// Enable Timer1 interrupt
    T3CONbits.TON = 1; 		// Start Timer

    T4CONbits.TON = 0; 		// Disable Timer
    T4CONbits.TCS = 0; 		// Select internal instruction cycle clock
    T4CONbits.TGATE = 0; 	// Disable Gated Timer mode
    T4CONbits.TCKPS = 1;        // prescaler: 1/8
    T4CONbits.T32 = 0;
    PR4 = 4096; //4096*8 = 0.233ms
    TMR4 = 0x00; 			// Clear timer register
    IPC6bits.T4IP = 0x01; 		// Set Timer1 Interrupt Priority Level to 6 = very high priority
    IFS1bits.T4IF = 0; 		// Clear Timer1 Interrupt Flag
    IEC1bits.T4IE = 0; 		// Enable Timer1 interrupt
    T4CONbits.TON = 1; 		// Start Timer
#endif
    motor_info.newData = 0;
    motor_info.t1 = 0;
    motor_info.t2 = 0;
    motor_info.t3 = 0;
    PMSM_Init(&motor_info);

    motor_state.init_return = RET_OK;
    return motor_state.init_return;
}

void pmsm_enable(unsigned enable)
{
    EN_GATE = enable;
}

void pmsm_update()
{
    static float t=0;
    float a,b,c;
    float p;
    t+=0.001;
    p = powf(t,2.)*10.;
    //TODO: set rotor position
    SetTorque(.5);
    //SetPosition(p);
    //p = 3.141592;
    if(t<1.){
        SetPosition(p);
    } else {
        p = (t+1)*150.;
        SetPosition(p);
    }
    SetTorque(.3);
    SetPosition(motor_state.rotor_state+2*3.14/6);
    motor_info.newData = 0;
    PMSM_Update();
    
    pmsm_set_duty_cycle((uint16_t)(motor_info.t1/100.*4096),(uint16_t)(motor_info.t2/100.*4096),(uint16_t)(motor_info.t3/100.*4096));
    //pmsm_set_duty_cycle(0,2000,2000);
    /*t++;
    b = sin((0.15*t)+3.14*2/3)/2+0.5;
    a = sin((0.15*t))/2+0.5;
    c = sin((0.15*t)+3.14*4/3)/2+0.5;
    if(a>b)
        if(b>c)
            c=0;
        else
            b=0;
    else
        if(c>b)
            a=0;
        else if (c>a)
            a=0;
        else
            c=0;


    pmsm_set_duty_cycle((uint16_t)(a*4096),(uint16_t)(b*4096),(uint16_t)(c*4096));*/
}

void pmsm_set_duty_cycle(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3)
{
    PDC1 = pwm1;
    PDC2 = pwm2;
    PDC3 = pwm3;
#ifdef PIC_MC
    
#else
    if(pwm1>4096)
        pwm1 = 4096;
    if(pwm2>4096)
        pwm2 = 4096;
    if(pwm3>4096)
        pwm3 = 4096;
    
    if(pwm1){
        PWM1 = 1;
        t2_ontime = 4096-pwm1;
        t2_offtime = pwm1;
        TMR2 = t2_ontime;
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
    } else {
       PWM1 = 0;
       IEC0bits.T2IE = 0;
    }
    if(pwm2){
        PWM3 = 1;
        t3_ontime = 4096-pwm2;
        t3_offtime = pwm2;
        TMR3 = t3_ontime;
        IFS0bits.T3IF = 0;
        IEC0bits.T3IE = 1;
    } else {
       PWM3 = 0;
       IEC0bits.T3IE = 0;
    }
    if(pwm3){
        PWM5 = 1;
        t4_ontime = 4096-pwm3;
        t4_offtime = pwm3;
        TMR4 = t4_ontime;
        IFS1bits.T4IF = 0;
        IEC1bits.T4IE = 1;
    } else {
       PWM5 = 0;
       IEC1bits.T4IE = 0;
    }
#endif
}

#ifndef PIC_MC


void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void)
{
    if(PWM1){
        TMR2 = t2_offtime;
    } else {
        TMR2 = t2_ontime;
    }
    PWM1 = !PWM1;
    IFS0bits.T2IF = 0; // Clear Timer 2 Interrupt Flag
}
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
    if(PWM3){
        TMR3 = t3_offtime;
    } else {
        TMR3 = t3_ontime;
    }
    PWM3 = !PWM3;
    IFS0bits.T3IF = 0; // Clear Timer 3 Interrupt Flag
}
void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void)
{
    if(PWM5){
        TMR4 = t4_offtime;
    } else {
        TMR4 = t4_ontime;
    }
    PWM5 = !PWM5;
    IFS1bits.T4IF = 0; // Clear Timer 4 Interrupt Flag
}
#endif
#endif