/* 
 * File:   power_timers.c
 * Author: jonathan
 *
 * Created on March 21, 2014, 11:04 AM
 */

#include "p33Exxxx.h"
#include "power_state.h"
#include "power_timers.h"

timer_data timer_state;

return_value_t timers_init()
{
    /* Set timer 1 as main clock */
    T1CONbits.TON = 0; 		// Disable Timer
    T1CONbits.TCS = 0; 		// Select internal instruction cycle clock
    T1CONbits.TGATE = 0; 	// Disable Gated Timer mode
    T1CONbits.TCKPS = 1;        // prescaler: 1/8
    PR1 = 8750;                 //8750*8=70000 = 1ms

    TMR1 = 0x00; 			// Clear timer register
    IPC0bits.T1IP = 0x06; 		// Set Timer1 Interrupt Priority Level to 6 = very high priority
    IFS0bits.T1IF = 0; 		// Clear Timer1 Interrupt Flag
    IEC0bits.T1IE = 1; 		// Enable Timer1 interrupt
    T1CONbits.TON = 1; 		// Start Timer
    timer_state.systime = 0;
    timer_state.init_return = RET_OK;
    return timer_state.init_return;
}

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    ++timer_state.systime;
    IFS0bits.T1IF = 0; // Clear Timer 1 Interrupt Flag
}
