#include "p33Exxxx.h"
#include "sensor_timers.h"
#include "sensor_state.h"

timer_data timer_state;

return_value_t timers_init()
{
    /* Set timer 1 as main clock */
    T1CONbits.TON = 0; 		// Disable Timer
    T1CONbits.TCS = 0; 		// Select internal instruction cycle clock
    T1CONbits.TGATE = 0; 	// Disable Gated Timer mode
    T1CONbits.TCKPS = 1;        // prescaler: 1/8
    PR1 = 8750; //8750*8=70000 = 1ms

    TMR1 = 0x00; 			// Clear timer register
    IPC0bits.T1IP = 0x06; 		// Set Timer1 Interrupt Priority Level to 6 = very high priority
    IFS0bits.T1IF = 0; 		// Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; 		// Enable Timer1 interrupt
    T1CONbits.TON = 1; 		// Start Timer
    timer_state.systime = 0;
    timer_state.init_return = RET_OK;
    return timer_state.init_return;

    /****************************************
     * Initializes Timer 4 for DWM1000
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
}

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    ++timer_state.systime;
    IFS0bits.T1IF = 0; // Clear Timer 1 Interrupt Flag
}
