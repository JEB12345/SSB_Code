#include <adc.h>
#include <stdio.h>
#include <stdlib.h>
#include <dma.h>
#include "../include/config.h"
#include PICINCLUDE
#include "../include/clock.h"
#include "../include/pindefs.h"

unsigned int ADCbufA[3][8] __attribute__((aligned(32 * 16)));
unsigned int ADCbufB[3][8] __attribute__((aligned(32 * 16)));
/*
struct{
     unsigned int Adc1Ch0[8];
     unsigned int Adc1Ch1[8];
     unsigned int Adc1Ch12[8];
     //unsigned int Adc1Ch3[8];
 } ADCbufA __attribute__((aligned(32 * 16)));

 struct{
     unsigned int Adc1Ch0[8];
     unsigned int Adc1Ch1[8];
     unsigned int Adc1Ch12[8];
     //unsigned int Adc1Ch2[8];
     //unsigned int Adc1Ch3[8];
 } ADCbufB __attribute__((aligned(32 * 16)));*/

void initDMA3(void)         {
    unsigned int config;
    unsigned int irq;
    unsigned int pad_address;
    unsigned int count;
     DMA3CONbits.AMODE  = 2;        //
     DMA3CONbits.MODE   = 2;        //
     config = DMA0CON|0b1000000000000000;
     pad_address            = 0x0300;   // Point to ADC1BUF0
     count            = 31-8;
     irq            = 13;
     OpenDMA3( config, irq, (long unsigned int)ADCbufA,
        (long unsigned int)ADCbufB,pad_address, count );

     IFS2bits.DMA3IF    = 0;
     IEC2bits.DMA3IE    = 1;

     DMA3CONbits.CHEN   = 1;
 }

void initTimer3()           {
     TMR3           = 0x0000;
     PR3            = 4999;     // Trigger every 125 uS
     IFS0bits.T3IF  = 0;
     IEC0bits.T3IE  = 0;

     T3CONbits.TON  = 1;        // Turn ON timer 3
 }

unsigned int DmaBuffer = 0;
void __attribute__((interrupt, no_auto_psv)) _DMA3Interrupt(void){
    unsigned i;
     if(DmaBuffer == 0)
     {
         LED2=(ADC1BUF0>500);
         /*ProcessADCSamples(BufferA.Adc1Ch0);
         ProcessADCSamples(BufferA.Adc1Ch1);
         ProcessADCSamples(BufferA.Adc1Ch2);
         ProcessADCSamples(BufferA.Adc1Ch3);*/
         //LED2 = ADCbufA[2][0]>0;
         //LED2_OFF;
         for(i=0; i<8;++i){
             if(ADCbufA[2][i]>0 || ADCbufA[0][i]>0 || ADCbufA[1][i]>0){
                 LED2_ON;
                 break;
             }
         }

     }
     else
     {
         for(i=0; i<8;++i){
             if(ADCbufB[2][i]>0 || ADCbufB[0][i]>0 || ADCbufB[1][i]>0){
                 LED2_ON;
                 break;
             }
         }
         /*
         ProcessADCSamples(BufferB.Adc1Ch0);
         ProcessADCSamples(BufferB.Adc1Ch1);
         ProcessADCSamples(BufferB.Adc1Ch2);
         ProcessADCSamples(BufferB.Adc1Ch3);*/
         //LED2 = ADCbufA[2][0]>0;
     }
     LED1_TOGGLE;
     DmaBuffer ^= 1;

     IFS2bits.DMA3IF = 0;
 }


void adc_init()
{
    LED2_OFF;
    AD1CON1bits.ADON   = 0;        // Turn ADC off

     AD1CON1bits.FORM   = 0;        // Data Output format
     AD1CON1bits.SSRC   = 0b111;
     AD1CON1bits.SSRCG = 0;
    // AD1CON1bits.SSRC   = 2;        // Sample Clock Source: GP timer
     AD1CON1bits.ASAM   = 1;        // Convert immediately after sampling
     AD1CON1bits.AD12B  = 1;        // Sample multiple channels individually

     AD1CON2bits.BUFM   = 0;        //
     AD1CON2bits.CSCNA  = 1;        //
     AD1CON2bits.CHPS   = 0;        //

     AD1CON3bits.ADRC   = 0;
     AD1CON3bits.ADCS   = 200;
     AD1CON3bits.SAMC = 20;

     //AD1CHS0: A/D Input Select Register
     AD1CHS0bits.CH0SA  = 0;
     AD1CHS0bits.CH0NA  = 0;

     //AD1CHS123: A/D Input Select Register
     AD1CHS123bits.CH123SA  = 0;
     AD1CHS123bits.CH123NA  = 0;

     AD1CSSL = 0x1003;              // Scan AN0, AN1, AN12 inputs

     AD1CON1bits.ADDMABM    = 0;
     AD1CON2bits.SMPI   = 3-1;
     AD1CON4bits.DMABL  = 3; //8 words buffer per input
     AD1CON4bits.ADDMAEN = 1;
     IFS0bits.AD1IF     = 0;
     IEC0bits.AD1IE     = 0;
     
     //initTimer3();
     initDMA3();
     AD1CON1bits.ADON   = 1;
}

