/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 14, 2013, 3:41 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"
#include PICINCLUDE
#include "../include/clock.h"
#include "../include/pindefs.h"
#include "../include/util.h"
#include "../../../libs/ECAN_dspic/ecanFunctions.h"
#include <math.h>

volatile uint16 pos1_i, pos2_i, pos3_i;
/* Timer 1 is used as system timer */
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    static uint16 state = 0;
    LED1_TOGGLE;
    PWM1 = pos1_i>state;
    PWM3 = pos2_i>state;
    PWM5 = pos3_i>state;


    if(++state>256){
        state=0;
        LED2_TOGGLE;
    }

IFS0bits.T1IF = 0; // Clear Timer 1 Interrupt Flag
}


void timer_init()
{
	/* Set timer 1 as main clock */
	T1CONbits.TON = 0; 		// Disable Timer
	T1CONbits.TCS = 0; 		// Select internal instruction cycle clock
	T1CONbits.TGATE = 0; 	// Disable Gated Timer mode

        PR1 = 50;


	TMR1 = 0x00; 			// Clear timer register
	IPC0bits.T1IP = 0x06; 		// Set Timer1 Interrupt Priority Level to 6 = very high priority
	IFS0bits.T1IF = 0; 		// Clear Timer1 Interrupt Flag
	IEC0bits.T1IE = 1; 		// Enable Timer1 interrupt
	T1CONbits.TON = 1; 		// Start Timer

}

/*
 * 
 */
int main() {
    clock_init();
    pin_init();
    ecan1msgBuf;
    double time = 0.;
    double curtime, pos1, pos2, pos3;
    LED1_ON;
    EN_GATE = 1;
    /*
    while(1){
    delay_ms(100);
    PWM1 = !PWM1;
    LED1_TOGGLE;
    LED2_TOGGLE;
    LED3_TOGGLE;
    LED4_TOGGLE;
    }
     */
    timer_init();
    while(1){
        LED3 = !FAULT;
        LED4 = !OCTW;
        delay_us(100);
        time += 0.0001;
        curtime = 1000.*time*3.14*2.;
        pos1 = (cos(curtime)+1.)*0.5;
        pos2 = (cos(curtime+2.09)+1.)*0.5;
        pos3 = (cos(curtime+4.18)+1.)*0.5;
        pos1_i = (uint16)(pos1*256);
        pos2_i = (uint16)(pos2*256);
        pos3_i = (uint16)(pos3*256);

    }

}

