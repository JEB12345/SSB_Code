/* 
 * File:   power_adc.c
 * Author: jonathan
 *
 * Created on March 25, 2014, 8:52 AM
 */

#include <p33Exxxx.h>
#include "power_adc.h"
#include "power_pindef.h"
#include "power_state.h"

__eds__ int BufferA[4] __attribute__((eds,aligned(4)));
__eds__ int BufferB[4] __attribute__((eds,aligned(4)));

analog_data adc_values;

return_value_t init_adc()
{
    /*******************************
     * Initializes the ADC Module
     *******************************/
    AD1CON1bits.ADON = 0;       //Turn off Module
    //AD1CON1 Settings
    AD1CON1bits.ADSIDL = 0;     //Continues module operation in Idle mode
    AD1CON1bits.ADDMABM = 0;    //Don't Care ignored by DMA
    AD1CON1bits.AD12B = 1;      //12-bit, 1-CH operation
    AD1CON1bits.FORM = 0b00;    //Unsignd Integer output
    AD1CON1bits.SSRC = 0b010;   //Timer3 compare ends sampling and starts conversion
    AD1CON1bits.SSRCG = 0;      //Default no external triggering?
    AD1CON1bits.SIMSAM = 0;     //Has to be off for 12-bit mode
    AD1CON1bits.ASAM = 1;       //Auto sampling, SAMP bit is auto-set

    //AD1CON2 Settigns
    AD1CON2bits.VCFG = 0b000;   //Vrefh = AVdd, Vrefl = AVss
    AD1CON2bits.CSCNA = 1;      //Scans inputs for CH0+ during Sample
    AD1CON2bits.CHPS = 0b00;    //Converts CH0
    AD1CON2bits.SMPI = 0b0010;  //Increments the DMA address after completion of every 4 sample/conversion operation
    AD1CON2bits.BUFM = 0;       //Always starts filling the buffer from the Start address
    AD1CON2bits.ALTS = 0;       //Always uses channel input selects for Sample MUXA

    //AD1CON3 Settings
    AD1CON3bits.ADRC = 0;       //ADC internal RC clock
    AD1CON3bits.ADCS = 63;      //ADC Conversion Clock

    //AD1CON4 Settings
    AD1CON4bits.ADDMAEN = 1;    //Use DMA
    AD1CON4bits.DMABL = 0b011;  //Allocates 8 words of buffer to each analog input

    //AD1CHS0 Settigns
    AD1CHS0bits.CH0NA = 0;      //Channel 0 negative input is V REFL

    //AD1CSSL Settings
    AD1CSSL = 0x00;             // Scan Selection Bits, 1=scan
    AD1CSSLbits.CSS6 = 1;       
    AD1CSSLbits.CSS7 = 1;
    AD1CSSLbits.CSS8 = 1;
    AD1CSSLbits.CSS11 = 1;

    //Flags and Interrupts
    IFS0bits.AD1IF = 0;         //Clear ADC Interrupt flag bit
    IEC0bits.AD1IE = 0;         //Disable ADC interrupt

    /****************************************
     * Initializes Timer 3 for ADC Triggering
    *****************************************/
    T2CONbits.TON = 0;          //Stop any 2/3 timer
    T2CONbits.T32 = 0;          //Sets Timer 2 and Timer 3 as separate 15-bit timers
    T3CONbits.TON = 0;          //Disables the Timer 3 module
    T3CONbits.TSIDL = 0;        //Coninuous mode during idle
    T3CONbits.TGATE = 0;        //Gated time accumulation disabled
    T3CONbits.TCKPS = 0b10;     //1:64 Prescaler
    T3CONbits.TCS = 0;          //Use Internal Clock (Fp)

    //Settings the Loop Time
    PR3 = 1;                //Fp / (TCKPS*PR3) = LoopTime => 70000000/(64*8750)=125us
    TMR3 = 0x00;                //Clear Timer 3 register
    IPC2bits.T3IP = 0x06;       //Set Timer 3 Interrupt Priority
    IFS0bits.T3IF = 0;          //Clear Timer 3 Interrupt Flag
    IEC0bits.T3IE = 1;          //Enable Timer 3 Interrupt

    /*******************************
     * Initializes the DMA0 Module
     *******************************/
    DMA0CONbits.AMODE = 0b10;   //Peripheral indirect mode w/ post-increment
    DMA0CONbits.MODE = 0b10;    //Continuous Ping-Pong mode
    IFS0bits.DMA0IF = 0;        //Clear the DMA Interrupt Flag bit
    IEC0bits.DMA0IE = 0;        //Disable DMA CH0 Interrupt
    DMA0CONbits.CHEN = 0;       //Disable DMA0 for Configuration
    DMA0CONbits.SIZE = 1;       //Data is Byte Sized
    DMA0CONbits.DIR = 0;        //Peripheral to DMA
    DMA0CNT = 31;               //32 DMA requests
    DMA0REQ = 13;               //Select ADC1 as DMA source
    DMA0PAD = (volatile unsigned int)&ADC1BUF0; //Points DMA to ADC buffer

    DMA0STBL = __builtin_dmaoffset(BufferA);
    DMA0STBH = 0x0000;

    DMA0STAL = __builtin_dmaoffset(BufferB);
    DMA0STAH = 0x0000;

    IFS0bits.DMA0IF = 0;        //Clear the DMA Interrupt Flag bit
    IEC0bits.DMA0IE = 1;        //Enable DMA Interrupt bit

    /*********************
     * Turning on Modules
     *********************/
    T3CONbits.TON = 1;          //Start Timer 3
    DMA0CONbits.CHEN = 1;       //Enable DMA
    AD1CON1bits.ADON = 1;       //Turn on the ADC

    return RET_OK;
}

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
    static uint8_t DMAbuffer = 0;
    static uint8_t ADC_State = 0;
    if(DMAbuffer){
        LED_3 = 1;
        switch(ADC_State){
            case 0:
                adc_values.AN6 = BufferA[ADC_State];
                ADC_State++;
                break;
            case 1:
                adc_values.AN7 = BufferA[ADC_State];
                ADC_State++;
                break;
            case 2:
                adc_values.AN8 = BufferA[ADC_State];
                ADC_State++;
                break;
            case 3:
                adc_values.AN11 = BufferA[ADC_State];
                ADC_State = 0;
                break;
            default:
                ADC_State = 0;
        }
    }
    else{
        LED_3 = 0;
        switch(ADC_State){
            case 0:
                adc_values.AN6 = BufferB[ADC_State];
                ADC_State++;
                break;
            case 1:
                adc_values.AN7 = BufferB[ADC_State];
                ADC_State++;
                break;
            case 2:
                adc_values.AN8 = BufferB[ADC_State];
                ADC_State++;
                break;
            case 3:
                adc_values.AN11 = BufferB[ADC_State];
                ADC_State = 0;
                break;
            default:
                ADC_State = 0;
        }
    }
    DMAbuffer ^= 1;

    IFS0bits.DMA0IF = 0;        //Clear the DMA Interrupt Flag bit
}

void __attribute__((__interrupt__, auto_psv)) _T3Interrupt(void)
{
    IFS0bits.T3IF = 0; // Clear Timer 3 Interrupt Flag
}
