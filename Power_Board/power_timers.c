/* 
 * File:   power_timers.c
 * Author: jonathan
 *
 * Created on March 21, 2014, 11:04 AM
 */

#include "p33Exxxx.h"
#include "power_state.h"
#include "power_timers.h"
#include "power_can.h"

extern can_data can_state;

timer_data timer_state;

return_value_t timers_init() {
    /****************************************
     *  Set timer 1 as main clock
     *****************************************/
    T1CONbits.TON = 0; // Disable Timer
    T1CONbits.TCS = 0; // Select internal instruction cycle clock
    T1CONbits.TGATE = 0; // Disable Gated Timer mode
    T1CONbits.TCKPS = 1; // prescaler: 1/8
    PR1 = 8750; //8750*8=70000 = 1ms (millisecond, 1 kHz)

    TMR1 = 0x00; // Clear timer register
    IPC0bits.T1IP = 0x06; // Set Timer1 Interrupt Priority Level to 6 = very high priority
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; // Enable Timer1 interrupt
    timer_state.systime = 0;
    /****************************************/


    /****************************************
     * Timer 2/3 is used for the CanFestival
     * Library and is set in timer_dspic.c
     *****************************************/


    /****************************************
     * Initializes Timer 4 for Buzzer and
     * other fast reliable Toggling
     *****************************************/
    T4CONbits.TON = 0; //Stop any 4/5 timer
    T4CONbits.T32 = 0; //Sets Timer 4 and Timer 5 as separate 15-bit timers
    T4CONbits.TON = 0; //Disables the Timer 4 module
    T4CONbits.TSIDL = 0; //Stop during idle
    T4CONbits.TGATE = 0; //Gated time accumulation disabled
    T4CONbits.TCKPS = 0b01; //1:8 Prescaler
    T4CONbits.TCS = 0; //Use Internal Clock (Fp)

    //Settings the Loop Time
    TMR4 = 0x00; //Clear Timer 4 register
    PR4 = 0xFFFF; //Fp / (TCKPS*PR4) = LoopTime => 70000000/(8xPR4)=100000Hz
    IFS1bits.T4IF = 0; //Clear Timer 4 Interrupt Flag
    IEC1bits.T4IE = 1; //enable/disable Timer 4 Interrupt
    /****************************************/


    /****************************************
     * Initializes Timer 5 for ADC Triggering
     *****************************************/
    T4CONbits.TON = 0; //Stop any 4/5 timer
    T4CONbits.T32 = 0; //Sets Timer 4 and Timer 5 as separate 15-bit timers
    T5CONbits.TON = 0; //Disables the Timer 5 module
    T5CONbits.TSIDL = 0; //Coninuous mode during idle
    T5CONbits.TGATE = 0; //Gated time accumulation disabled
    T5CONbits.TCKPS = 0b00; //1:1 Prescaler
    T5CONbits.TCS = 0; //Use Internal Clock (Fp)

    //Settings the Loop Time
    TMR5 = 0x00; //Clear Timer 5 register
    PR5 = 100; //Fp / (TCKPS*PR5) = LoopTime => 70000000/7000 = 10000Hz
    //70000000/(1*140)=500000Hz
    IFS1bits.T5IF = 0; //Clear Timer 5 Interrupt Flag
    IEC1bits.T5IE = 1; //Enable Timer 5 Interrupt
    /****************************************/

    /****************************************
     * Inint Timers
     */
    T1CONbits.TON = 1; // Start Timer
    T4CONbits.TON = 1; //Start Timer 4
    T5CONbits.TON = 1; //Start Timer 5
    /****************************************/

    timer_state.fasttime = 0; //Init counter for high speed, synced timer
    timer_state.ext_time_100us = 0;
    timer_state.ext_time_seconds = 0;
    timer_state.init_return = RET_OK;
    return timer_state.init_return;
}

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void) {
    ++timer_state.systime;
    IFS0bits.T1IF = 0; // Clear Timer 1 Interrupt Flag
}

void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void) {
    IFS1bits.T4IF = 0; // Clear Timer 4 Interrupt Flag
}

void __attribute__((__interrupt__, auto_psv)) _T5Interrupt(void) {
    static uint16_t last_fasttime = 0;
    static uint16_t fast_time_wrapper = 0; //old interrupt was running 70 times slower
    if(fast_time_wrapper++>69){
        fast_time_wrapper = 0;
        //timer 5 is a continuously running timer
        ++timer_state.fasttime;
        ++timer_state.ext_time_100us;
        if (timer_state.ext_time_100us >= 10000) {
            timer_state.ext_time_100us = 0;
            ++timer_state.ext_time_seconds;
        }

        CO(nrf_time) = (((uint32_t)timer_state.ext_time_seconds&0xFFFF) << 16) | (((uint32_t)timer_state.ext_time_100us&0xFFFF));
    }
    IFS1bits.T5IF = 0; // Clear Timer 5 Interrupt Flag
}
