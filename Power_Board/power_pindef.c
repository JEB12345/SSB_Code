/* 
 * File:   power_pindef.c
 * Author: jonathan
 *
 * Created on March 20, 2014, 2:11 PM
 */

#include "power_pindef.h"

return_value_t pin_init() {

    //Set all pins to input
    TRISA = 0xFFFF;
    TRISB = 0xFFFF;
    TRISC = 0xFFFF;
    TRISD = 0xFFFF;
    TRISE = 0xFFFF;
    TRISF = 0xFFFF;
    TRISG = 0xFFFF;

    //Configure all analog ports as digital I/O
    ANSELA = 0x0;
    ANSELB = 0x0;
    ANSELC = 0x0;
    ANSELE = 0x0;

    //Watchdog
    PTGCONbits.PTGWDT = 0b000; //watchdog disabled

    //LEDs
    TRISAbits.TRISA12 = 0;  //LED_1
    TRISAbits.TRISA11 = 0;  //LED_2
    TRISAbits.TRISA0 = 0;   //LED_3
    TRISAbits.TRISA1 = 0;   //LED_STATUS

    //Power & Motor Enable Pins
    TRISBbits.TRISB15 = 0;  //BACKUP_CHARGE_EN
    TRISDbits.TRISD5 = 0;   //EN_BACKUP_5V5
    TRISDbits.TRISD6 = 0;   //EN_MAIN_5V5
    TRISAbits.TRISA10 = 0;  //EN_24V_5V5_IC
    TRISDbits.TRISD8 = 0;   //MOTOR_EN
    TRISBbits.TRISB4 = 0;   //EN_MOTOR_CURRENT
    TRISAbits.TRISA4 = 0;   //G_BAT_PIC
    TRISAbits.TRISA8 = 0;   //G_BAT_KILL

    //5V5 Output Control Pins
    TRISBbits.TRISB9 = 0;   //EN_OUT_1
    TRISCbits.TRISC6 = 0;   //EN_OUT_2
    TRISCbits.TRISC13 = 0;  //EN_OUT_3
    TRISBbits.TRISB8 = 0;   //EN_OUT_4

    //ANALOG PINS
    ANSELCbits.ANSC0 = 1;
    ANSELCbits.ANSC1 = 1;
    ANSELCbits.ANSC2 = 1;
    ANSELCbits.ANSC11 = 1;

    //UART 1
    _RP37R = 0b000001;              //U1TX to pin RP37/RB5 = EX_1
    RPINR18bits.U1RXR = 0b0100110;  //U1RX to pin RP38/RB6 = EX_2

    return RET_OK;
}

