/* 
 * File:   pindefs.h
 * Author: ken
 *
 * Created on August 14, 2013, 8:32 PM
 */

/*
	Copyright (C) 2011-2012 Michiel D'Haene <michiel.dhaene at gmail dot com>,
        Ken Caluwaerts <ken@caluwaerts.eu>

	UGent Reservoir lab (http://reslab.elis.ugent.be/michiel)
	Ghent University (http://www.ugent.be)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PINDEFS_H
#define PINDEFS_H
#ifdef	__cplusplus
extern "C" {
#endif

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
#define     LED1_ON     (LED1=1)
#define     LED1_OFF    (LED1=0)
#define     LED1_TOGGLE (LED1=!LED1)
#define     LED2_ON     (LED2=1)
#define     LED2_OFF    (LED2=0)
#define     LED2_TOGGLE (LED2=!LED2)
#define     LED3_ON     (LED3=1)
#define     LED3_OFF    (LED3=0)
#define     LED3_TOGGLE (LED3=!LED3)
#define     LED4_ON     (LED4=1)
#define     LED4_OFF    (LED4=0)
#define     LED4_TOGGLE (LED4=!LED4)

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
#define     RB4     PORTBbits.RB4


void pin_init();

#ifdef	__cplusplus
}
#endif

#endif // PINDEFS_H



