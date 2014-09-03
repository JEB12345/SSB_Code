#include "p33Exxxx.h"
#include "motor_state.h"
#include "motor_pindefs.h"

return_value_t pin_init()
{
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

    /*
     * Watchdog
     */
    PTGCONbits.PTGWDT = 0b000; //watchdog disabled

    /*
     * CAN
     */
    TRISFbits.TRISF1 = 0; //TX = output
    TRISFbits.TRISF0 = 1;
    _RP97R = 0b001110;//TX
    RPINR26bits.C1RXR = 96; //RX

    /*
     * PWM signals: output
    */
    TRISBbits.TRISB14 = 0; 
    TRISBbits.TRISB12 = 0; 
    TRISBbits.TRISB10 = 0;
    _RP42R = 0x0;

    /*
    * Solder jumpers: input
    */
    _RP118R = 0;
    _RP120R = 0;

    /*
    * LEDs: output
    */
    TRISCbits.TRISC10 = 0;
    TRISBbits.TRISB7 = 0;
    TRISCbits.TRISC13 = 0;
    TRISBbits.TRISB8 = 0;
    _RP39R = 0;
    _RP40R = 0;
    CVRCONbits.CVR1OE = 0;
    I2C1CONbits.I2CEN = 0;

    /*
    * Motor encoder
    */
    RPINR14bits.QEA1R = 52;
    RPINR14bits.QEB1R = 51;
    RPINR15bits.INDX1R = 25;

    /*
    * Motor current (analog) inputs
    */
    ANSELAbits.ANSA0 = 1;
    ANSELAbits.ANSA1 = 1;

    /*
     * Motor control stuff
     */
    _RP56R = 0;
    _RP55R = 0;
    _RP54R = 0;
    _RP41R = 0;
    TRISCbits.TRISC6 = 0; //EN_GATE is output
    TRISCbits.TRISC7 = 0; //GAIN is output
    TRISBbits.TRISB9 = 0; //DC_CAL is output


    /*
     * JP5 pins: config if needed
     */
    //UART TX on AN5/RP35
    _RP35R = 0b000001;
    TRISBbits.TRISB3 = 0;
    //UART RX on AN4/RPI34
    RPINR18bits.U1RXR = 34;
    
    /*
     * JP2 pins: config if needed
     */

    /*
     * JP1 pins: config if needed
     */
    //pins: 29 30 31
    //Hall sensors
    //ENABLE PULL-UPS
    /*
    CNPUEbits.CNPUE14 = 1;
    CNPUEbits.CNPUE15 = 1;
    CNPUAbits.CNPUA8 = 1;*///PULL UPS ARE TOO WEAK!!!
    //peripheral pin select
    RPINR7bits.IC1R = 94;
    RPINR7bits.IC2R = 95;
    RPINR8bits.IC3R = 24;

    //SG UART2:
    //TX: RB4: RP36
    //RX: RB1: RPI33
    TRISBbits.TRISB4 = 0;
    _RP36R = 3;
    RPINR19bits.U2RXR = 33;

    /* Disable comparators */
    CM1CONbits.CEN = 0;
    CM2CONbits.CEN = 0;
    CM3CONbits.CEN = 0;

    CVRCONbits.CVR1OE = 0;
    I2C1CONbits.I2CEN = 0;
    
    return RET_OK;
}