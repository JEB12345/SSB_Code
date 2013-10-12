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

uint8_t TxBufferKEN[100] __attribute__((aligned(32 * 16)));
uint8_t RxBufferKEN[100] __attribute__((aligned(32 * 16)));
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
    
    //IPC8bits.SPI2IP = 6;        // Sets the Interrupt Prioriety to 6

    // SPI2CON1 Register Settings
    SPI2CON1bits.DISSCK = 0;    // Internal Serial Clock is Enabled
    SPI2CON1bits.DISSDO = 0;    // SDO2 pin is controlled by the module
    SPI2CON1bits.MODE16 = 0;    // Communication is 0=8-bits, 1=16bits wide

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
    //DMA2REQbits.FORCE=1;
    //while (DMA2REQbits.FORCE == 1);
    IEC2bits.SPI2IE = 0;        // Enable the Interrupt
    

    /*********************
     * DMA2 TX Configuration
     *********************/
    IFS1bits.DMA2IF = 0;        // Clear the DMA Interrupt Flag bit
    IPC6bits.DMA2IP = 0b000;
    DMA2CONbits.CHEN = 0;       // Disable DMA3 for Configuration
    DMA2CONbits.SIZE = 1;       // Data is Byte sized
    DMA2CONbits.DIR = 1;        // Read RAM, Write to Perifpheral
    DMA2CONbits.HALF = 0;       // Interrupt when all data is moved
    DMA2CONbits.NULLW = 0;      // Normal Opertaion
    DMA2CONbits.AMODE = 0b00;   // Register Indirect w/ Post-Increment
    DMA2CONbits.MODE = 0b01;//0b10;    // Continuous, Ping-Pong Enabled

    config = DMA2CON | 0b1000000000000000;
    irq = 0b00100001;                   // Setting for SPI2 Transfer
    count = 1;                  // Nuber of Bytes exchanged
    pad_address = (volatile unsigned int) &SPI2BUF; //Name of SPI2 shared buffer
    stb_address = 0x0;

    // Open DMA call to setup DMA
    OpenDMA2(config, irq,(long unsigned int)TxBufferKEN, stb_address, pad_address, count);
//    DMA2CNT = 0;                // DMA3CNT + 1 DMA Requests
 //   DMA2REQbits.IRQSEL = 33;    // DMA Peripheral set to SPI2 Transfer Done

   // DMA2PAD = (volatile unsigned int) &SPI2BUF;

   // DMA2STAL = (unsigned int) &TxBufferA;
    //DMA2STAH = 0x0000;

    //DMA2STBL = (unsigned int) &TxBufferB;
    //DMA2STBH = 0x0000;

    IEC1bits.DMA2IE = 0;        // Clears the DMA Interrupt Enable bit
    DMA2CONbits.CHEN = 1;       // Enable DMA Channel

    /*********************
     * DMA3 RX Configuration
     *********************/
    IFS2bits.DMA3IF = 0;        // Clear the DMA Interrupt Flag bit
    IPC9bits.DMA3IP = 0b001;
    DMA3CONbits.CHEN = 0;       // Disable DMA3 for Configuration
    DMA3CONbits.SIZE = 1;       // Data is Byte sized
    DMA3CONbits.DIR = 0;        // Read Peripheral, Write to RAM
    DMA3CONbits.HALF = 0;       // Interrupt when all data is moved
    DMA3CONbits.NULLW = 0;      // Normal Write Opertaion
    DMA3CONbits.AMODE = 0b00;   // Register Indirect w/ Post-Increment
    DMA3CONbits.MODE = 0b00;    // Continuous, Ping-Pong Enabled

    config = DMA3CON | 0b1000000000000000;
    irq = 33;                   // Setting for SPI2 Transfer
    count = 1;                  // Nuber of Bytes exchanged
    pad_address = (volatile unsigned int) &SPI2BUF; //Name of SPI2 shared buffer
    stb_address = 0x0;

    // Open DMA call to setup DMA
    OpenDMA3(config, irq, (long unsigned int) RxBufferKEN, stb_address, pad_address, count);
    //DMA3CNT = 0;                // DMA3CNT + 1 DMA Requests
    //DMA3REQbits.IRQSEL = 33;    // DMA Peripheral set to SPI2 Transfer Done

    //DMA3PAD = (volatile unsigned int) &SPI2BUF;

    //DMA3STAL = (unsigned int) &RxBufferA;
    //DMA3STAH = 0x0000;

    //DMA3STBL = (unsigned int) &RxBufferB;
    //DMA3STBH = 0x0000;

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
    uint32_t i,j;
    bool fail;

    LED_1 = 0;
    LED_2 = 0;
    LED_3 = 0;
    LED_4 = 0;
    XBEE_nSSEL = 1;
    fail = 1;
    for(i=0;i<XBEE_RESET_RETRIES && fail;++i){
        XBEE_nRESET = 1;
        for(j=0;j<10000;++j){
            XBEE_nRESET = 1;
        }
        XBEE_nRESET = 0;
        XBEE_DOUT_OUTPUT;
        XBEE_DOUT = 0;
        LED_1 = 1;
        LED_2 = 1;
        j=0;
        while(XBEE_nATTN && (j++)<XBEE_RESET_WAIT_CYCLES);
        fail = XBEE_nATTN;
        XBEE_nRESET = 1;
        XBEE_DOUT_INPUT;
    }
    if(fail){
        rf_state.init_XBEE_return = RET_ERROR;
        return rf_state.init_XBEE_return;
    }
    LED_3 = 1;

    tx_spi_buffer_array[0] = 0x01;
    tx_spi_buffer_array[1] = 0x02;
    tx_spi_buffer_array[2] = 0x03;
    TxBufferKEN[0]= 1;
    TxBufferKEN[1]= 2;
    TxBufferKEN[2]= 3;

    DMA2CONbits.CHEN = 0;
    DMA3CONbits.CHEN = 0;
    DMA2CNT = 2;
    DMA3CNT = 2;
    DMA2CONbits.CHEN = 1;
    DMA3CONbits.CHEN = 1;
    uint32_t dma2 = rf_state.dma2_int_cnt;
    uint32_t dma3 = rf_state.dma3_int_cnt;

    //SPI2BUF = tx_spi_buffer_array[0];
    XBEE_nSSEL = 0;
    
    DMA2REQbits.FORCE = 1;//start transfer
    //wait for dma interrupt
    while(dma3==rf_state.dma3_int_cnt){
        LED_4 = 1;
    }
    LED_4 = 0;
    if(RxBufferKEN[0]==0x7E){
        LED_1 = 1;
    } else {
        LED_1 = 0;
    }
    XBEE_nSSEL = 1;

    

    //DO IT AGAIN TO MAKE SURE:)
    XBEE_nSSEL = 0;
    for(i=0;i<16*50;++i){
    TxBufferKEN[i]= SPI_BUFFER_SIZE-i;
    }
    TxBufferKEN[0] = RxBufferKEN[0];
    TxBufferKEN[1] = RxBufferKEN[1];
    TxBufferKEN[2] = RxBufferKEN[2];
    DMA2CONbits.CHEN = 0; //NEEDED OR WE CAN ONLY DO ONE TRANSFER!!!
    DMA3CONbits.CHEN = 0;
    DMA2CNT = SPI_BUFFER_SIZE-1;
    DMA3CNT = SPI_BUFFER_SIZE-1;
    DMA2CONbits.CHEN = 1;
    DMA3CONbits.CHEN = 1;
    dma3 = rf_state.dma3_int_cnt;

    DMA2REQbits.FORCE = 1;//start transfer
    //wait for dma interrupt
    while(dma3==rf_state.dma3_int_cnt){
        LED_3 = 1;
    }
    LED_3 = 0;
    XBEE_nSSEL = 1;

    rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_IP;

    rf_state.init_XBEE_return = RET_OK;
    return rf_state.init_XBEE_return;
}

return_value_t rf_init()
{
    //init state
    rf_state.xbee_state = XBEE_STATE_INIT;
    rf_state.xbee_at_req = 0;
    rf_state.dma2_int_cnt = rf_state.dma3_int_cnt = 0;
    rf_state.init_return = RET_OK;
    //init spi & dma
    spi2_init();
    if(rf_state.init_SPI2_return!=RET_OK){
        rf_state.init_return = RET_ERROR;
        return rf_state.init_return;
    }
    //init xbee
    xbee_init();
    if(rf_state.init_XBEE_return!=RET_OK){
        rf_state.init_return = RET_ERROR;
    }
    
    return rf_state.init_return;
}


void rf_process()
{
    //Handle received packets
    switch(rf_state.xbee_state){
        case XBEE_STATE_IDLE_TRANSMIT_IP:
        case XBEE_STATE_IDLE_TRANSMIT_AT:
            //check for data in the raw incoming buffer            
            break;
        case XBEE_STATE_TRANSMIT:
        case XBEE_STATE_TRANSMITTED:
        case XBEE_STATE_PACKET_RECEIVED:
        case XBEE_STATE_INIT:
        case XBEE_STATE_RECEIVE_HEADER:
        case XBEE_STATE_RECEIVE_FRAME:
        default:
            //don't handle incoming data while still receiving/sending or when there's an error
            break;
    };

    //Update the state
    switch(rf_state.xbee_state){
        case XBEE_STATE_TRANSMIT:
            //do nothing, wait till transmitted becomes active after DMA interrupt
            break;
        case XBEE_STATE_IDLE_TRANSMIT_IP:
            if(XBEE_nATTN){
                if(rf_state.xbee_at_req){
                    //go to TRANSMIT_AT MODE
                    rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_AT;
                } else {
                    //at_req is not asserted, remain in transmit_ip mode
                    //TODO: if there's an IP packet to send, start sending it and go to XBEE_STATE_TRANSMIT
                    if(CB_ReadMany(&rf_state.ip_tx_buffer,&rf_state.cur_tx_ip_packet,sizeof(xbee_tx_ip_packet_t))){
                        rf_state.xbee_state = XBEE_STATE_RECEIVE_HEADER;
                        //xbee_transmit_packet(rf_state.cur_ip_packet.raw_data, rf_state.cur_ip_packet.raw_data_length);
                    }
                }
            } else {
                //go to receive
            }
            break;
        case XBEE_STATE_IDLE_TRANSMIT_AT:
            if(XBEE_nATTN){
                if(rf_state.xbee_at_req){
                    //check if there's AT data to send
                    //TODO: if there's an AT command to send, start sending it and go to XBEE_STATE_TRANSMIT
                } else {
                    //at_req was disabled, go back to transmit_ip mode
                    rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_IP;
                }
            } else {
                //go to receive
            }
            break;
        case XBEE_STATE_TRANSMITTED:
        case XBEE_STATE_PACKET_RECEIVED:
            //go back to IDLE_TRANSMIT_IP or IDLE_TRANSMIT_AT depending on the at_req flag
            if(rf_state.xbee_at_req){
                rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_AT;
            } else {
                rf_state.xbee_state = XBEE_STATE_IDLE_TRANSMIT_IP;
            }
            break;
        case XBEE_STATE_RECEIVE_FRAME:
            //do nothing, wait till XBEE_STATE_PACKET_RECEIVED is active after the second receive DMA interrupt
            break;
        case XBEE_STATE_RECEIVE_HEADER:
            //do nothing, we will go to XBEE_STATE_RECEIVE_FRAME automatically after a DMA interrupt
            break;
        case XBEE_STATE_INIT:
        default:
            //error!!!
            break;
    };
}

/***************************
 *  SPI2 DMA3 Receive Interrupt
 ***************************/
void __attribute__((__interrupt__, __auto_psv__)) _DMA3Interrupt(void)
{
    static unsigned int RxBufferCount = 0;    // Keep record of the RX data buffer

    switch(rf_state.xbee_state){
        case XBEE_STATE_TRANSMIT:
            //finished sending data, go to XBEE_STATE_TRANSMITTED
            XBEE_nSSEL = 1;
            //TODO: free packet pointer if necessary.
            rf_state.xbee_state = XBEE_STATE_TRANSMITTED;
            break;
        case XBEE_STATE_RECEIVE_FRAME:
            //full packet received
            //TODO: put in raw RX buffer
            rf_state.xbee_state = XBEE_STATE_PACKET_RECEIVED;
            XBEE_nSSEL = 1;
            break;
        case XBEE_STATE_RECEIVE_HEADER:
            //read N bytes (rest of packet)
            //TODO: allocate memory for rx buffer
            break;
        case XBEE_STATE_IDLE_TRANSMIT_IP:            
        case XBEE_STATE_IDLE_TRANSMIT_AT:            
        case XBEE_STATE_TRANSMITTED:
        case XBEE_STATE_PACKET_RECEIVED:        
        case XBEE_STATE_INIT:
        default:
            //error, we should never be in any of these states!
            break;
    };

    rf_state.dma3_int_cnt++;
    //LED_1 = 0;

    RxBufferCount ^= 1;
    IFS2bits.DMA3IF = 0;
}

void __attribute__((__interrupt__, __auto_psv__)) _INT2Interrupt(void)
{
    
}
