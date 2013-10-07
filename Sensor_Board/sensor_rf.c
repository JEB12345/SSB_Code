/*
 *  File:   sensor_spi.c
 *  Author: Jonathan Bruce
 *
 *  Created on: 24th September 2013
 *
 */

#include <p33Exxxx.h>
#include <dma.h>
#include "sensor_rf.h"
#include "sensor_pindefs.h"
#include "sensor_state.h"
#include "superball_circularbuffer.h"
#include "xbee_API.h"

#ifndef SPI_BUFFER_SIZE
#define SPI_BUFFER_SIZE 16*50
#endif

rf_data rf_state;
CircularBuffer TxCB;
CircularBuffer RxCB;

uint8_t tx_spi_buffer_array[SPI_BUFFER_SIZE];
uint8_t rx_spi_buffer_array[SPI_BUFFER_SIZE];


/*
 * DMA2 Tx Buffers
 */
unsigned int TxBufferA[16] __attribute__((space(xmemory)));
unsigned int TxBufferB[16] __attribute__((space(xmemory)));
/*
 * DMA3 Rx Buffers
 */
unsigned int RxBufferA[16] __attribute__((space(xmemory)));
unsigned int RxBufferB[16] __attribute__((space(xmemory)));

/*
 * Sets Up the SPI2 line to interface with the XBee Wifi
 */
return_value_t spi2_init() {

    unsigned int config;
    unsigned int irq;
    unsigned long int stb_address;
    unsigned int pad_address;
    unsigned int count;

    // Setup Circular Buffers, Crash and Burn if FAIL
    if (!CB_Init(&TxCB, tx_spi_buffer_array, SPI_BUFFER_SIZE)) {
        LED_1 = 1;
        LED_2 = 1;
        LED_3 = 1;
        LED_4 = 1;
        while (1);
    }
    if (!CB_Init(&RxCB, rx_spi_buffer_array, SPI_BUFFER_SIZE)) {
        LED_1 = 1;
        LED_2 = 1;
        LED_3 = 1;
        LED_4 = 1;
        while (1);
    }

    rf_state.init_SPI2_return = RET_OK;
    /*
     * SPI2 Peripheral Pin Select
     * CLK = RP57/RC9
     * nSSEL = RP41/RB9
     * MISO = RP40/RB8
     * MOSI = RP39/RB7
     */

    /*********************
     * SPI2 Configuration
     *********************/
    SPI2STATbits.SPIEN = 0;     // Disable SPI2 for Configuration
    IFS2bits.SPI2IF = 0;        // Clear the Interrupt Flag
    IEC2bits.SPI2IE = 0;        // Diable the Intterupt
    IPC8bits.SPI2IP = 6;        // Sets the Interrupt Prioriety to 6

    // SPI2CON1 Register Settings
    SPI2CON1bits.DISSCK = 0;    // Internal Serial Clock is Enabled
    SPI2CON1bits.DISSDO = 0;    // SDO2 pin is controlled by the module
    SPI2CON1bits.MODE16 = 0;    // Communication is 0=8-bytes, 1=16bytes

    SPI2CON1bits.SMP = 0;       // Input Data is Sampled at the Middle of Data Output Time
    SPI2CON1bits.CKE = 0;       // Serial Output data changes on leading edge
    SPI2CON1bits.CKP = 0;       // Idle state for clock is logic level low
    SPI2CON1bits.MSTEN = 1;     // Master Mode Enabled
    // SPI Clock Freq of 3.5Mhz
    // Fsck = Fp/PPRE*SPRE => 3,500,000 = 70,000,000/(4*5)
    SPI2CON1bits.PPRE = 2;      // Primary Prescale 4:1
    SPI2CON1bits.SPRE = 3;      // Secondary Prescale 5:1

    // SPI2CON2 Register Settings
    SPI2CON2bits.FRMEN = 0;     // Framed Mode 0=Disabled, 1=Enabled
    SPI2CON2bits.SPIBEN = 0;    // Enhanced Buffer is Disabled
    
    // Interrupt Controller Settings
    IFS2bits.SPI2EIF = 0;       // Clear the SPI2 Error Interrupt Flag Status bit
    IFS2bits.SPI2IF = 0;        // CLear the Interrupt Flag
    IEC2bits.SPI2IE = 1;        // Enable the Interrupt

    /*********************
     * DMA2 TX Configuration
     *********************/
    IFS1bits.DMA2IF = 0;        // Clear the DMA Interrupt Flag bit

    DMA2CONbits.CHEN = 0;       // Disable DMA3 for Configuration
    DMA2CONbits.SIZE = 1;       // Data is Byte sized
    DMA2CONbits.DIR = 1;        // Read RAM, Write to Perifpheral
    DMA2CONbits.HALF = 0;       // Interrupt when all data is moved
    DMA2CONbits.NULLW = 0;      // Normal Opertaion
    DMA2CONbits.AMODE = 0b00;   // Register Indirect w/ Post-Increment
    DMA2CONbits.MODE = 0b10;    // Continuous, Ping-Pong Enabled

    config = DMA2CON | 0b1000000000000000;
    irq = 33;                   // Setting for SPI2 Transfer
    count = 7;                  // Nuber of Bytes exchanged
    pad_address = (volatile unsigned int) &SPI2BUF; //Name of SPI2 shared buffer
    stb_address = 0x0;

//    // Open DMA call to setup DMA
//    OpenDMA2(config, irq, (unsigned int) TxBufferA, stb_address, pad_address, count);
    DMA2CNT = 0;                // DMA3CNT + 1 DMA Requests
    DMA2REQbits.IRQSEL = 33;    // DMA Peripheral set to SPI2 Transfer Done

    DMA2PAD = (volatile unsigned int) &SPI2BUF;

    DMA2STAL = (unsigned int) &TxBufferA;
    DMA2STAH = 0x0000;

    DMA2STBL = (unsigned int) &TxBufferB;
    DMA2STBH = 0x0000;

    IEC1bits.DMA2IE = 1;        // Set the DMA Interrupt Enable bit
    DMA2CONbits.CHEN = 1;       // Enable DMA Channel

    /*********************
     * DMA3 RX Configuration
     *********************/
    IFS2bits.DMA3IF = 0;        // Clear the DMA Interrupt Flag bit

    DMA3CONbits.CHEN = 0;       // Disable DMA3 for Configuration
    DMA3CONbits.SIZE = 1;       // Data is Byte sized
    DMA3CONbits.DIR = 0;        // Read Peripheral, Write to RAM
    DMA3CONbits.HALF = 0;       // Interrupt when all data is moved
    DMA3CONbits.NULLW = 0;      // Normal Write Opertaion
    DMA3CONbits.AMODE = 0b00;   // Register Indirect w/ Post-Increment
    DMA3CONbits.MODE = 0b10;    // Continuous, Ping-Pong Enabled

    config = DMA3CON | 0b1000000000000000;
    irq = 33;                   // Setting for SPI2 Transfer
    count = 7;                  // Nuber of Bytes exchanged
    pad_address = (volatile unsigned int) &SPI2BUF; //Name of SPI2 shared buffer
    stb_address = 0x0;

//    // Open DMA call to setup DMA
//    OpenDMA3(config, irq, (unsigned int) RxBufferA, stb_address, pad_address, count);
    DMA3CNT = 0;                // DMA3CNT + 1 DMA Requests
    DMA3REQbits.IRQSEL = 33;    // DMA Peripheral set to SPI2 Transfer Done

    DMA3PAD = (volatile unsigned int) &SPI2BUF;

    DMA3STAL = (unsigned int) &RxBufferA;
    DMA3STAH = 0x0000;

    DMA3STBL = (unsigned int) &RxBufferB;
    DMA3STBH = 0x0000;

    IEC2bits.DMA3IE = 1;        // Set the DMA Intterupt Enable bit
    DMA3CONbits.CHEN = 1;       // Enable DMA Channel

    /*********************
     * SPI2 Enable and DMA Force
     *********************/
//    DMA2REQbits.FORCE = 1;      // Force first two words to fillin Tx Buffer
//    while(DMA2REQbits.FORCE == 1);
//
//    DMA3REQbits.FORCE = 1;      // Force first two words to fillin Tx Buffer
//    while(DMA3REQbits.FORCE == 1);

//    SPI2STATbits.SISEL = 0b011;  // Interrupt when the SPIx receive buffer is full (SPIxRBF bit set)
    SPI2STATbits.SPISIDL = 0;   // Contine Module in Idle Mode
    SPI2STATbits.SPIROV = 0;    // Clear Overflow Flag
    SPI2STATbits.SPIEN = 1;     // Enable SPI Module

    
    return rf_state.init_SPI2_return;
}

/*
 * XBEE Init function.
 */
return_value_t xbee_init() {
    nRESET = 0;
    while(!nRESET){
        if(!XBEE_nATTN){
            XBEE_nSSEL = 0;
            //SPI2BUF = 0x07;
            DMA2REQbits.FORCE = 1;      // Force first two words to fillin Tx Buffer
            nRESET = 1;
            LED_2 = 1;
            return rf_state.init_XBEE_return = RET_OK;
        }
    }
    return rf_state.init_XBEE_return = RET_ERROR;
}

/*
 * XBEE Rx Test Function
 */
void xbee_rx_test() {
    
}


/***************************
 * SPI2 Interrupt
 ***************************/
void __attribute__((__interrupt__, __auto_psv__)) _SPI2Interrupt(void)
{
    CB_WriteMany(&RxCB, SPI2BUF, 2, 1);
    DMA2REQbits.FORCE = 1;
    IFS2bits.SPI2IF = 0;
    if(RxCB.overflowCount > 0){
        LED_4 = 1;
    }
}

/***************************
 * SPI2 DMA2 Transmit Interrupt
 ***************************/
void __attribute__((__interrupt__, __auto_psv__)) _DMA2Interrupt(void)
{
    static unsigned int TxBufferCount = 0;    // Keep record of the TX data buffer

    TxBufferCount ^= 1;
    IFS1bits.DMA2IF = 0;
}

/***************************
 *  SPI2 DMA3 Receive Interrupt
 ***************************/
void __attribute__((__interrupt__, __auto_psv__)) _DMA3Interrupt(void)
{
    static unsigned int RxBufferCount = 0;    // Keep record of the RX data buffer

    if(RxBufferCount == 0) {
        CB_WriteMany(&RxCB, SPI2BUF, sizeof(wifi_data), 1);
    }
    else {
        CB_WriteMany(&RxCB, SPI2BUF, sizeof(wifi_data), 1);
    }

    RxBufferCount ^= 1;
    IFS2bits.DMA3IF = 0;
}

void __attribute__((__interrupt__, __auto_psv__)) _INT2Interrupt(void)
{
    
}
