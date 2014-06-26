/* 
 * File:   pindefs.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:55 PM
 */

#ifndef PINDEFS_H
#define	PINDEFS_H
#include "sensor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif

return_value_t pin_init();

//LEDs
#define RGB_RED     LATGbits.LATG8
#define RGB_BLUE    LATGbits.LATG6
#define RGB_GREEN   LATAbits.LATA0
#define LED_1       LATDbits.LATD6
#define LED_4       LATDbits.LATD5 //incorrect in the schematic D3->D5
#define LED_3       LATCbits.LATC13
#define LED_2       LATDbits.LATD8

//IMU
#define INT_IMU     PORTFbits.RF0 //actually tied to INT1

//RF
#define XBEE_nATTN  PORTEbits.RE14//actually tied to INT2
#define XBEE_nSSEL  LATBbits.LATB9
#define XBEE_SLEEP_RQ    LATFbits.LATF1
#define XBEE_nRESET      LATEbits.LATE13
#define XBEE_DOUT   LATCbits.LATC10
#define XBEE_DOUT_INPUT (TRISCbits.TRISC10 = 1)
#define XBEE_DOUT_OUTPUT (TRISCbits.TRISC10 = 0)

//POWER MOSFETS
#define NFET_1      LATCbits.LATC12
#define NFET_2      LATCbits.LATC15
#define NFET_3      LATAbits.LATA10

//LOAD CELL
#define SHD         LATCbits.LATC6
#define SS          LATBbits.LATB0
#define SG_MISO     PORTAbits.RA9

//Pin Out Connectors
//ANALOG pins -> analog input specified in ADC module if needed
//other pins -> define direction here
#define PIN_OUTPUT  1
#define PIN_INPUT   0

//P6 connector
#define RB14_IO        PIN_OUTPUT
#define RG9_IO         PIN_INPUT
#define RA11_IO        PIN_OUTPUT
#define RA1_IO         PIN_OUTPUT
#define RB2_IO         PIN_INPUT
#define RB15_IO        PIN_INPUT
#define RA12_IO        PIN_INPUT
#define RG7_IO         PIN_OUTPUT
#define RB1_IO         PIN_INPUT
#define RB3_IO         PIN_INPUT

//P7 connector
#define RE12_IO        PIN_INPUT
#define RA8_IO         PIN_INPUT
#define RB11_IO        PIN_INPUT
#define RB13_IO        PIN_OUTPUT
#define RE13_IO        PIN_INPUT
#define RB4_IO         PIN_OUTPUT
#define RC10_IO        PIN_INPUT
#define RA7_IO         PIN_INPUT
#define RB10_IO        PIN_OUTPUT
#define RB12_IO        PIN_INPUT

#if RB14_IO==PIN_INPUT
#define P6_RB14    PORTBbits.RB14
#else
#define P6_RB14    LATBbits.LATB14
#endif

#if RG9_IO==PIN_INPUT
#define P6_RG9    PORTGbits.RG9
#else
#define P6_RG9    LATGbits.LATG9
#endif

#if RA11_IO==PIN_INPUT
#define P6_RA11    PORTAbits.RA11
#else
#define P6_RA11    LATAbits.LATA11
#endif

#if RA1_IO==PIN_INPUT
#define P6_RA1    PORTAbits.RA1
#else
#define P6_RA1    LATAbits.LATA1
#endif

#if RB2_IO==PIN_INPUT
#define P6_RB2    PORTBbits.RB2
#else
#define P6_RB2    LATBbits.LATB2
#endif

#if RB15_IO==PIN_INPUT
#define P6_RB15    PORTBbits.RB15
#else
#define P6_RB15    LATBbits.LATB15
#endif

#if RA12_IO==PIN_INPUT
#define P6_RA12    PORTAbits.RA12
#else
#define P6_RA12    LATAbits.LATA12
#endif

#if RG7_IO==PIN_INPUT
#define P6_RG7    PORTGbits.RG7
#else
#define P6_RG7    LATGbits.LATG7
#endif

#if RB1_IO==PIN_INPUT
#define P6_RB1    PORTBbits.RB1
#else
#define P6_RB1    LATBbits.LATB1
#endif

#if RB3_IO==PIN_INPUT
#define P6_RB3    PORTBbits.RB3
#else
#define P6_RB3    LATBbits.LATB3
#endif

#if RE12_IO==PIN_INPUT
#define P7_RE12    PORTEbits.RE3
#else
#define P7_RE12    LATEbits.LATE3
#endif

#if RA8_IO==PIN_INPUT
#define P7_RA8    PORTAbits.RA8
#else
#define P7_RA8    LATAbits.LATA8
#endif

#if RB11_IO==PIN_INPUT
#define P7_RB11    PORTBbits.RB11
#else
#define P7_RB11    LATBbits.LATB11
#endif

#if RB13_IO==PIN_INPUT
#define P7_RB13    PORTBbits.RB13
#else
#define P7_RB13    LATBbits.LATB13
#endif

#if RE13_IO==PIN_INPUT
#define P7_RE13    PORTEbits.RE13
#else
#define P7_RE13    LATEbits.LATE13
#endif

#if RB4_IO==PIN_INPUT
#define P7_RB4    PORTBbits.RB4
#else
#define P7_RB4    LATBbits.LATB4
#endif

#if RC10_IO==PIN_INPUT
#define P7_RC10    PORTCbits.RC10
#else
#define P7_RC10    LATCbits.LATC10
#endif

#if RA7_IO==PIN_INPUT
#define P7_RA7    PORTAbits.RA7
#else
#define P7_RA7    LATAbits.LATA7
#endif

#if RB10_IO==PIN_INPUT
#define P7_RB10    PORTBbits.RB10
#else
#define P7_RB10    LATBbits.LATB10
#endif

#if RB12_IO==PIN_INPUT
#define P7_RB12    PORTBbits.RB12
#else
#define P7_RB12    LATBbits.LATB12
#endif

/*
 * Motor control stuff
 */
#define     OCTW    PORTBbits.RB1
#define     FAULT   PORTBbits.RB2
#define     EN_GATE LATAbits.LATA1
#define     HALL1   PORTBbits.RB15
#define     HALL2   PORTGbits.RG7
#define     HALL3   PORTGbits.RG9

#ifdef	__cplusplus
}
#endif

#endif	/* PINDEFS_H */

