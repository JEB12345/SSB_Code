/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 14, 2013, 3:41 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <dma.h>
#include "../include/config.h"
#include PICINCLUDE
#include "../include/clock.h"
#include "../include/pindefs.h"
#include "../include/util.h"
//#include "../../../libs/ECAN_dspic/ecanFunctions.h"
#include <math.h>

volatile uint16 pos1_i, pos2_i, pos3_i;
/* Timer 1 is used as system timer */
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    static uint16 state = 0;
    //LED4 = !FAULT;
    PWM1 = pos1_i>state;
    PWM3 = pos2_i>state;
    PWM5 = pos3_i>state;
    LED1 = PWM1;
    LED2 = PWM3;
    LED3 = PWM5;

    if(++state>256){
        state=0;
    }

    IFS0bits.T1IF = 0; // Clear Timer 1 Interrupt Flag
}


void timer_init()
{
	/* Set timer 1 as main clock */
	T1CONbits.TON = 0; 		// Disable Timer
	T1CONbits.TCS = 0; 		// Select internal instruction cycle clock
	T1CONbits.TGATE = 0; 	// Disable Gated Timer mode

        PR1 = 50;
        
	TMR1 = 0x00; 			// Clear timer register
	IPC0bits.T1IP = 0x06; 		// Set Timer1 Interrupt Priority Level to 6 = very high priority
	IFS0bits.T1IF = 0; 		// Clear Timer1 Interrupt Flag
	IEC0bits.T1IE = 1; 		// Enable Timer1 interrupt
	T1CONbits.TON = 1; 		// Start Timer

}

unsigned int ecan1MsgBuf[32][8] __attribute__((aligned(32 * 16)));

void can_init()
{
    unsigned int config;
    unsigned int irq;
    unsigned long int stb_address;
    unsigned int pad_address;
    unsigned int count;
    // 0 normal, 1 disable, 2 loopback, 3 listen-only, 4 configuration, 7 listen all messages
    uint8 desired_mode = 0;//(parameters[0] & 0x001C) >> 2;
    
    //CONFIG CAN
    // Make sure the ECAN module is in configuration mode.
    // It should be this way after a hardware reset, but
    // we make sure anyways.
    C1CTRL1bits.REQOP = 4;
    while (C1CTRL1bits.OPMODE != 4);

    //1Mbaud
    C1CFG1bits.BRP = 4; //TQ= FCAN/10 = 14Mhz = 14 TQ/bit
    C1CFG1bits.SJW = 0;//(parameters[3] & 0x0600) >> 9;
    C1CFG2bits.SEG1PH = 3;//4*TQ//a; // Set segment 1 time
    C1CFG2bits.PRSEG = 4;//5*TQ//b; // Set propagation segment time
    C1CFG2bits.SEG2PHTS = 0x1; // Keep segment 2 time programmable
    C1CFG2bits.SEG2PH = 3;//4*TQ //c; // Set phase segment 2 time
    C1CFG2bits.SAM = (0x0800) >> 11; // Triple-sample for majority rules at bit sample point

    // Setup our frequencies for time quanta calculations.
    // FCAN is selected to be FCY*2 = FP*2 = 140Mhz
    C1CTRL1bits.CANCKS = 1;
    C1FCTRL = 0xC01F; // No FIFO, 32 Buffers
    // Setup message filters and masks.
    C1CTRL1bits.WIN = 1; // Allow configuration of masks and filters
    C1CTRL1bits.WIN = 0;

    // Clear all interrupt bits
    C1RXFUL1 = C1RXFUL2 = C1RXOVF1 = C1RXOVF2 = 0x0000;

    // Enable interrupts for ECAN1
    IEC2bits.C1IE = 1; // Enable interrupts for ECAN1 peripheral
    C1INTEbits.TBIE = 1; // Enable TX buffer interrupt
    C1INTEbits.RBIE = 1; // Enable RX buffer interrupt
    
    // Configure buffer settings.
    C1TR01CON = 0;
    //buffer 0 is transmit
    C1TR01CONbits.TX0PRI = 3;
    C1TR01CONbits.TXEN0 = 1;

    desired_mode = 0;
    C1CTRL1bits.REQOP = desired_mode;
    while (C1CTRL1bits.OPMODE != desired_mode);

    //CONFIG DMA
    DMA0CONbits.SIZE = 0;
    DMA0CONbits.DIR = 0x1;
    DMA0CONbits.AMODE = 0x2;
    DMA0CONbits.MODE = 0x0;
    config = DMA0CON|0b1000000000000000;
    irq = 70; //CAN TX
    count = 7;   //
    pad_address = (volatile unsigned int)&C1TXD;
    //sta_address = ecan1MsgBuf;
    stb_address = 0x0;
    OpenDMA0( config, irq, (long unsigned int)ecan1MsgBuf,
        stb_address,pad_address, count );
}

void can_test(){
    LED1_ON;

    ecan1MsgBuf[0][0] = 0x123C;
    ecan1MsgBuf[0][1] = 0x0000;
    ecan1MsgBuf[0][2] = 0x0008;
    ecan1MsgBuf[0][3] = 0x1;
    ecan1MsgBuf[0][4] = 0x2;
    ecan1MsgBuf[0][5] = 0x3;
    ecan1MsgBuf[0][6] = 0xabcd;
    LED2_ON;
    C1TR01CONbits.TXREQ0 = 0x1;
    LED3_ON;

    while(C1TR01CONbits.TXREQ0 == 1){
        delay_ms(100);
        LED4_TOGGLE;
    }

    LED4_ON;
}

/*
 * 
 */
int main() {    
    double time = 0.;
    double curtime, pos1, pos2, pos3;
    //unsigned i;
    clock_init();
    pin_init();
    can_init();
    EN_GATE = 1;
    can_test();
    while(1);

    /*
    //msg = malloc(sizeof(tCanMessage));
    while(1){
    CANTXmsg.id = 100;
    CANTXmsg.buffer = 0;
    CANTXmsg.message_type = CAN_MSG_DATA;
    CANTXmsg.frame_type = CAN_FRAME_STD;
    for(i=0;i<8;++i){
        CANTXmsg.payload[i] = i;
    }
    CANTXmsg.validBytes = 8;

    ecan1_buffered_transmit(&CANTXmsg);
    delay_ms(200);
    LATBbits.LATB4 = !LATBbits.LATB4;
    LED1_TOGGLE;
    }
     */
    //timer_init();
    while(1){        
        delay_us(100);
        time += 0.0001;
        curtime = 20.*time*3.14*2.;
        pos1 = (cos(curtime)+1.)*0.5;
        pos2 = (cos(curtime+2.09)+1.)*0.5;
        pos3 = (cos(curtime+4.18)+1.)*0.5;
        pos1_i = (uint16)(pos1*256);
        pos2_i = (uint16)(pos2*256);
        pos3_i = (uint16)(pos3*256);  
    }

}

