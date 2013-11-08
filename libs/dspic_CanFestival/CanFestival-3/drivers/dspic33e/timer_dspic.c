/*
This file is part of CanFestival, a library implementing CanOpen Stack.

Copyright (C): Edouard TISSERANT and Francis DUPIN
AVR Port: Andreas GLAUSER and Peter CHRISTEN

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

// AVR implementation of the  CANopen timer driver, uses Timer 3 (16 bit)

// Includes for the Canfestival driver
#include "../../include/dspic33e/applicfg.h"
#include "../../include/timer.h"
#include <p33Exxxx.h>

//NOTE TO JONATHAN: I'm using TIMER2/3 in 32 bit mode

/************************** Modul variables **********************************/
// Store the last timer value to calculate the elapsed time
static volatile TIMEVAL last_time_set = 0;

void initTimer(void)
/******************************************************************************
Initializes the timer, turn on the interrupt and put the interrupt time to zero
INPUT	void
OUTPUT	void
******************************************************************************/
{
     /* Set timer 1 as main clock */
    T2CONbits.TON = 0; 		// Disable Timer
    T2CONbits.TCS = 0; 		// Select internal instruction cycle clock
    T2CONbits.TGATE = 0; 	// Disable Gated Timer mode
    T2CONbits.TCKPS = 1;        // prescaler: 1/8
    T2CONbits.T32 = 1;          //32 bit mode
    PR2 = 0xFFFF;
    PR3 = 0xFFFF;
    TMR3HLD = 0x00;
    TMR2 = 0x00; 			// Clear timer register
    TMR3 = 0x00;
    IFS0bits.T2IF = 0; 		// Clear Timer2 Interrupt Flag
    IEC0bits.T2IE = 0; 		// Disable Timer2 interrupt
    
    IPC2bits.T3IP = 0x06; 		// Set Timer3 Interrupt Priority Level to 6 = very high priority
    IFS0bits.T3IF = 0; 		// Clear Timer3 Interrupt Flag 
    IEC0bits.T3IE = 0; 		// Disable Timer3 interrupt for now

    T2CONbits.TON = 1; 		// Start Timer
}

void setTimer(TIMEVAL value)
/******************************************************************************
Set the timer for the next alarm.
INPUT	value TIMEVAL (unsigned long)
OUTPUT	void
******************************************************************************/
{
    uint32_t tmp;
    IEC0bits.T3IE = 0; 		// Disable Timer3 interrupt for now
    //store current elapsed time
    tmp = TMR3;
    tmp<<=16;
    last_time_set += TMR2;
    last_time_set += TMR3;
    TMR3HLD = 0;
    TMR2= 0;
    TMR3=0;
    PR2 = value&0xFFFF;
    PR3 = value>>16;
    IFS0bits.T3IF = 0; 		// Clear Timer3 Interrupt Flag
    IEC0bits.T3IE = 1; 		// Enabe Timer3 interrupt
}

inline TIMEVAL getElapsedTime(void)
/******************************************************************************
Return the elapsed time to tell the Stack how much time is spent since last call.
INPUT	void
OUTPUT	value TIMEVAL (unsigned long) the elapsed time
******************************************************************************/
{
    uint32_t tmp;
    TIMEVAL res;
    //store current elapsed time
    tmp = TMR3;
    tmp<<=16;
    last_time_set += TMR2;
    last_time_set += TMR3;
    res = last_time_set;
    last_time_set = 0;
    return res;
}

void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
    uint32_t tmp;

    IEC0bits.T3IE = 0; 	// Disable Timer3 interrupt
    IFS0bits.T1IF = 0; // Clear Timer 1 Interrupt Flag

    //store current elapsed time
    tmp = TMR3;
    tmp<<=16;
    last_time_set += TMR2;
    last_time_set += TMR3;

    //dispatch!
    TimeDispatch();   // Call the time handler of the stack to adapt the elapsed time
    //TODO: is there a way to do this in the main loop (might not be fast enough?)
}




