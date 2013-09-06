/* 
 * File:   pindefs.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:55 PM
 */

#ifndef PINDEFS_H
#define	PINDEFS_H
#include "motor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif

return_value_t pin_init();

/*
 * PWM signals
 */
#define     PWM1    LATBbits.LATB14//TODO: replace with PWM1H
#define     PWM3    LATBbits.LATB12
#define     PWM5    LATBbits.LATB10

/*
 * Solder jumpers
 */
#define     SJ1     PORTBbits.RB15
#define     SJ4     PORTGbits.RG6
#define     SJ5     PORTGbits.RG7
#define     SJ6     PORTGbits.RG8
#define     SJ7     PORTGbits.RG9
#define     SJADDRESS   ((SJ1<<4)|(SJ4<<3)|(SJ5<<2)|(SJ6<<1)|(SJ7))

/*
 * LEDs
 */
#define     LED1    LATCbits.LATC10
#define     LED2    LATBbits.LATB7
#define     LED3    LATCbits.LATC13
#define     LED4    LATBbits.LATB8

/*
 * Motor encoder
 */
#define     EN_A    PORTCbits.RC4
#define     EN_B    PORTCbits.RC3
#define     EN_C    PORTAbits.RA9

/*
 * Motor current (analog) inputs
 */
#define     CRNT1   PORTAbits.RA0
#define     CRNT2   PORTAbits.RA1

/*
 * Motor control stuff
 */
#define     PWRGD   PORTDbits.RD6
#define     OCTW    PORTDbits.RD5
#define     FAULT   PORTCbits.RC8
#define     GAIN    LATCbits.LATC7
#define     EN_GATE LATCbits.LATC6
#define     DC_CAL  LATBbits.LATB9

/*
 * JP5 pins
 */
#define     RA12    PORTAbits.RA12
#define     RA11    PORTAbits.RA11
#define     AN4     PORTAbits.RA4
#define     AN5     PORTAbits.RA5

/*
 * JP2 pins
 */
#define     RB1     PORTBbits.RB1
#define     RC0     PORTCbits.RC0
#define     RC1     PORTCbits.RC1
#define     RC2     PORTCbits.RC2

/*
 * JP1 pins
 */
#define     RE12    PORTEbits.RE12
#define     RE13    PORTEbits.RE13
#define     RE14    PORTEbits.RE14
#define     RE15    PORTEbits.RE15
#define     RA8     PORTAbits.RA8
#define     RB4



#ifdef	__cplusplus
}
#endif

#endif	/* PINDEFS_H */

