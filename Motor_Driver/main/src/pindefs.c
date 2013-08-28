/*

*/
#include "../include/config.h"
#include PICINCLUDE
#include "../include/pindefs.h"

void pin_init()
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
    * Motor encoder: TODO: the GP PIC has no quadrature encoder!
    */

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

    /*
     * JP2 pins: config if needed
     */

    /*
     * JP1 pins: config if needed
     */
    TRISBbits.TRISB4 = 0; //test output in on JP1

    /* Disable comparators */
    CM1CONbits.CEN = 0;
    CM2CONbits.CEN = 0;
    CM3CONbits.CEN = 0;
    
}


