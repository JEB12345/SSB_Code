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

//__eds__ uint16_t BufferA[8] __attribute__((eds,aligned(64)));
//__eds__ uint16_t BufferB[8] __attribute__((eds,aligned(64)));

__eds__ unsigned int BufferA[32] __attribute__((eds,aligned(64)));
__eds__ unsigned int BufferB[32] __attribute__((eds,aligned(64)));

analog_data adc_values;

return_value_t init_adc()
{
    /*******************************
     * Initializes the ADC Module
     *******************************/
    /**
     * Set port configuration
     */
    ANSELA = ANSELB = ANSELC = ANSELE = 0x0000;
    ANSELCbits.ANSC0 = 1;       //AN6
    ANSELCbits.ANSC1 = 1;       //AN7
    ANSELCbits.ANSC2 = 1;       //AN8
    ANSELCbits.ANSC11 = 1;      //AN11

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
    AD1CON2bits.SMPI = 0b0011;  //Increments the DMA address after completion of every 2 sample/conversion operation
    AD1CON2bits.BUFM = 0;       //Always starts filling the buffer from the start address
    AD1CON2bits.ALTS = 0;       //Always use channel input selects for Sample MUXA

    //AD1CON3 Settings
    AD1CON3bits.ADRC = 0;       //ADC internal RC clock
    AD1CON3bits.ADCS = 11;      //ADC Conversion Clock, Should be ~500kbps

    //AD1CON4 Settings
    AD1CON4bits.ADDMAEN = 1;    //Use DMA
    AD1CON4bits.DMABL = 0b011;  //Allocates 8 words of buffer to each analog input

    //AD1CHS0 Settigns
    AD1CHS0bits.CH0NA = 0;      //Channel 0 negative input is V REFL
    AD1CHS0bits.CH0SA = 0;      //CH0 positive set to AIN0

    //AD1CSSL Settings
    AD1CSSH = 0x00;
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
    TMR3 = 0x00;                //Clear Timer 3 register
    PR3 = 8750;                 //Fp / (TCKPS*PR3) = LoopTime => 70000000/(64*2188)=500us
    IFS0bits.T3IF = 0;          //Clear Timer 3 Interrupt Flag
    IEC0bits.T3IE = 1;          //Enable Timer 3 Interrupt

    /*******************************
     * Initializes the DMA0 Module
     *******************************/
    unsigned int config;
    unsigned int irq;
    unsigned long int stb_address;
    unsigned int pad_address;
    unsigned int count;

    IFS0bits.DMA0IF = 0;        //Clear the DMA Interrupt Flag bit
    IEC0bits.DMA0IE = 0;        //Disable DMA CH0 Interrupt

    DMA0CONbits.CHEN = 0;       //Disable DMA0 for Configuration
    DMA0CONbits.AMODE = 0b00;   //Register indirect mode w/ post-increment
    DMA0CONbits.MODE = 0b10;    //Continuous Ping-Pong mode
    DMA0CONbits.SIZE = 0;       //Data is Word Sized
    DMA0CONbits.DIR = 0;        //Peripheral to DMA
    DMA0CONbits.HALF = 0;       //Initiate interrupt when all of the data has been moved
    DMA0CONbits.NULLW = 0;      //Normal Opertaion

//    config = DMA0CON | 0b1000000000000000;
//    irq = 0b00001101;
//    count = 1;
//    pad_address = (volatile unsigned int)&ADC1BUF0; //Points DMA to ADC buffer
//    stb_address = 0x0;
//    OpenDMA0(config,irq,__builtin_dmaoffset(&BufferA),stb_address,pad_address,count);

    DMA0PAD = (volatile unsigned int)&ADC1BUF0; //Points DMA to ADC buffer
    DMA0CNT = 31;               //32 DMA request (4 buffers, each with 8 words)
    DMA0REQ = 13;               //Select ADC1 as DMA source

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
    Delay_us(20);

    return RET_OK;
}

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
    static uint8_t DMAbuffer = 1;
    static uint8_t ADC_State = 0;
    if(DMAbuffer){
        switch(ADC_State){
            case 0:
                adc_values.AN6 = BufferA[ADC_State];
                ADC_State++;
                //break;
            case 1:
                adc_values.AN7 = BufferA[ADC_State];
                ADC_State++;
               // break;
            case 2:
                adc_values.AN8 = BufferA[ADC_State];
                ADC_State++;
                // break;
            case 3:
                adc_values.AN11 = BufferA[ADC_State];
                ADC_State = 0;
                break;
            default:
                ADC_State = 0;
        }
    }
    else{
        switch(ADC_State){
            case 0:
                adc_values.AN6 = BufferB[ADC_State];
                ADC_State++;
                //break;
            case 1:
                adc_values.AN7 = BufferB[ADC_State];
                ADC_State++;
                //break;
            case 2:
                adc_values.AN8 = BufferB[ADC_State];
                ADC_State++;
                //break;
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

void __attribute__((__interrupt__, auto_psv)) _T4Interrupt(void)
{
    IFS0bits.T3IF = 0; // Clear Timer 3 Interrupt Flag
}

void Delay_us(unsigned int delay)
{
    uint16_t i;
    for (i = 0; i < delay; i++){
        __asm__ volatile ("repeat #39");
        __asm__ volatile ("nop");
    }
}
