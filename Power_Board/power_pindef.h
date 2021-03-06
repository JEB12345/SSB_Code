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
#define uC_KS_1             LATBbits.LATB4
#define uC_KS_2             LATEbits.LATE14
#define KILLSWITCH_nFAULT   PORTBbits.RB7

//RF Pins
#define RF_GND_EN           LATBbits.LATB13

#ifdef OLD_BOARD
#define VMOTOR_EN           LATDbits.LATD8
#else
#define VMOTOR_EN           PORTDbits.RD8
#endif

//5V5 Output Control Pins
#define EN_OUT_1            LATBbits.LATB9
#define EN_OUT_2            LATCbits.LATC6
#define EN_OUT_3            LATCbits.LATC13
#define EN_OUT_4            LATBbits.LATB8

//RF SPI Control
#define RF_IRQ              PORTGbits.RG9
#define RF_CE               LATAbits.LATA7
#define RF_CSN              LATBbits.LATB0
#define RF_MISO             LATAbits.LATA9
#define RF_GND_EN           LATBbits.LATB13
#define RF_BUF              SPI1BUF
/**
 Pin defines used in nRF library are located in nrf24l01.h
 */

//BUZZER
#define BUZZER              LATGbits.LATG8

//BATTERY CHARGER
#define VBACKUP_CHARGE_EN   LATBbits.LATB15
#define VBACKUP_STAT        PORTBbits.RB1
#define VBACKUP_CHARGER_ENABLE TRISBbits.TRISB15 = 0; VBACKUP_CHARGE_EN = 0
#define VBACKUP_CHARGER_DISABLE TRISBbits.TRISB15 = 1

#endif	/* POWER_PINDEF_H */

