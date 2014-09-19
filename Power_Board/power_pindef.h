/* 
 * File:   power_pindef.h
 * Author: jonathan
 *
 * Created on March 20, 2014, 1:21 PM
 */

#ifndef POWER_PINDEF_H
#define	POWER_PINDEF_H

#include "power_state.h"
#include <p33Exxxx.h>

//#define OLD_BOARD

return_value_t pin_init();

//LEDs
#define LED_R       LATAbits.LATA12
#define LED_G       LATAbits.LATA11
#define LED_B       LATAbits.LATA0
#define LED_STATUS  LATAbits.LATA1

//Power & Motor Enable Pins
#define EN_BACKUP_5V5       LATDbits.LATD5
#define EN_VBAT_5V5         LATDbits.LATD6 //Enables the output of Buck to 5v5 rail
#define VBAT_5V5_EN         LATAbits.LATA10 //Enables the Buck IC
#define KILLSWITCH_uC       LATAbits.LATA8
#define EN_MOTOR_CURRENT    LATEbits.LATE15

//RF Pins
#define RF_GND_EN           LATBbits.LATB13

#ifdef OLD_BOARD
#define VMOTOR_EN           LATDbits.LATD8
#endif

//5V5 Output Control Pins
#define EN_OUT_1            LATBbits.LATB9
#define EN_OUT_2            LATCbits.LATC6
#define EN_OUT_3            LATCbits.LATC13
#define EN_OUT_4            LATBbits.LATB8

#endif	/* POWER_PINDEF_H */

