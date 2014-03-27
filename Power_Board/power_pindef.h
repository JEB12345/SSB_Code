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

return_value_t pin_init();

//LEDs
#define LED_1       LATAbits.LATA12
#define LED_2       LATAbits.LATA11
#define LED_3       LATAbits.LATA0
#define LED_STATUS  LATAbits.LATA1

//Power & Motor Enable Pins
#define BACKUP_CHARGE_EN    LATBbits.LATB15
#define EN_BACKUP_5V5       LATDbits.LATD6
#define EN_MAIN_5V5         LATDbits.LATD5
#define EN_24V_5V5_IC       LATAbits.LATA10
#define MOTOR_EN            LATDbits.LATD8
#define EN_MOTOR_CURRENT    LATBbits.LATB4
#define G_BAT_PIC           LATAbits.LATA4
#define G_BAT_KILL          LATAbits.LATA8

//5V5 Output Control Pins
#define EN_OUT_1            LATBbits.LATB9
#define EN_OUT_2            LATCbits.LATC6
#define EN_OUT_3            LATCbits.LATC13
#define EN_OUT_4            LATBbits.LATB8


#endif	/* POWER_PINDEF_H */

