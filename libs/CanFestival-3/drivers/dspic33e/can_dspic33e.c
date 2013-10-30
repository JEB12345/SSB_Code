/*
This file is part of CanFestival, a library implementing CanOpen Stack.

Copyright (C): Edouard TISSERANT and Francis DUPIN
AVR Port: Andreas GLAUSER and Peter CHRISTEN

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

//#define DEBUG_WAR_CONSOLE_ON
//#define DEBUG_ERR_CONSOLE_ON

#include "../../include/dspic33e/can_dspic33e.h"
#include "../dspic33e/canfestival.h"
#include <p33Exxxx.h>

//internal RX buffer for CAN messages


static unsigned int ecan1RXMsgBuf[32][8];
static unsigned int ecan1TXMsgBuf[8];
#define CAN_RX_BUF_SIZE 5
static volatile Message rxbuffer[CAN_RX_BUF_SIZE]; //this is an internal buffer for received messages
static volatile uint8_t rxbuffer_start;
static volatile uint8_t rxbuffer_stop;

unsigned char canInit(unsigned int bitrate)
/******************************************************************************
Initialize the hardware to receive CAN messages and start the timer for the
CANopen stack.
INPUT	bitrate		bitrate in kilobit
OUTPUT	1 if successful	
******************************************************************************/
{
    unsigned int config;
    unsigned int irq;
    unsigned long int stb_address;
    unsigned int pad_address;
    unsigned int count;
    // 0 normal, 1 disable, 2 loopback, 3 listen-only, 4 configuration, 7 listen all messages
    uint8_t desired_mode = 0;//(parameters[0] & 0x001C) >> 2;
    rxbuffer_start = rxbuffer_stop = 0;
    if(bitrate!=1000000){
        //fail
        return 0;
    }

    //CONFIG CAN
    // Make sure the ECAN module is in configuration mode.
    // It should be this way after a hardware reset, but
    // we make sure anyways.
    C1CTRL1bits.REQOP = 4;
    while (C1CTRL1bits.OPMODE != 4);

    //1Mbaud
    C1CFG1bits.BRP = 4; //TQ= FCAN/10 = 14Mhz = 14 TQ/bit
    C1CFG1bits.SJW = 0;//(parameters[3] & 0x0600) >> 9;
    C1CFG2bits.PRSEG = 2;//5*TQ//b; // Set propagation segment time
    C1CFG2bits.SEG1PH = 4;//4*TQ//a; // Set segment 1 time
    C1CFG2bits.SEG2PHTS = 0x1; // Keep segment 2 time programmable
    C1CFG2bits.SEG2PH = 4;//4*TQ //c; // Set phase segment 2 time
    C1CFG2bits.SAM = (0x0800) >> 11; // Triple-sample for majority rules at bit sample point

    // Setup our frequencies for time quanta calculations.
    // FCAN is selected to be FCY*2 = FP*2 = 140Mhz
    C1CTRL1bits.CANCKS = 1;
    C1FCTRL = 0xC01F; // No FIFO, 32 Buffers

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

    desired_mode = 0b0;
    C1CTRL1bits.REQOP = desired_mode;
    while (C1CTRL1bits.OPMODE != desired_mode);

    //CONFIG DMA
    //TX
    DMA1CONbits.SIZE = 0; //word transfer mode
    DMA1CONbits.DIR = 0x1; //RAM to peripheral
    DMA1CONbits.AMODE = 0x2; //peripheral indirect addressing mode
    DMA1CONbits.MODE = 0x0; //continuous, no ping-pong
    config = DMA1CON|0b1000000000000000;
    irq = 70; //CAN TX
    count = 7;   //8 words per transfer
    pad_address = (volatile unsigned int)&C1TXD;
    //sta_address = ecan1MsgBuf;
    stb_address = 0x0;
    OpenDMA1( config, irq, (long unsigned int)ecan1TXMsgBuf,
        stb_address,pad_address, count );

    //RX
    DMA0CONbits.SIZE = 0;
    DMA0CONbits.DIR = 0; //Read to RAM from peripheral
    DMA0CONbits.AMODE = 2; // Continuous mode, single buffer
    DMA0CONbits.MODE = 0; // Peripheral Indirect Addressing
    config = DMA0CON|0b1000000000000000;
    irq = 0x22;// Select ECAN1 RX as DMA Request source
    count = 7;   //8 words per transfer
    IEC0bits.DMA0IE = 0; // Enable DMA Channel 0 interrupt
    //DMA0CONbits.CHEN = 1; // Enable DMA Channel 0
    pad_address = (volatile unsigned int)&C1RXD;
    stb_address = 0x0;
    OpenDMA0( config, irq, (long unsigned int)ecan1RXMsgBuf,
        stb_address,pad_address, count );


    // Setup message filters and masks.
    C1CTRL1bits.WIN = 1; // Allow configuration of masks and filters

    C1FMSKSEL1bits.F0MSK=0x0; //Filter 0 will use mask 0
    C1RXM0SIDbits.SID = 0b0; //accept all

    C1RXF0SIDbits.SID = 0;//0x123c;//0x1; //set filter

    C1RXM0SIDbits.MIDE = 0x1; //only receive standard frames
    C1RXF0SIDbits.EXIDE= 0x0;
    C1BUFPNT1bits.F0BP = 0x1; //use message buffer 1 to receive data
    C1FEN1bits.FLTEN0=0x1; //enable channel

    C1CTRL1bits.WIN = 0;

    // Clear all interrupt bits
    C1RXFUL1 = C1RXFUL2 = C1RXOVF1 = C1RXOVF2 = 0x0000;

    // Enable interrupts for ECAN1
    IEC2bits.C1IE = 1; // Enable interrupts for ECAN1 peripheral
    C1INTEbits.TBIE = 1; // Enable TX buffer interrupt
    C1INTEbits.RBIE = 1; // Enable RX buffer interrupt
    return 1;
}

char canSend(CAN_PORT notused, Message *m)
/******************************************************************************
The driver send a CAN message passed from the CANopen stack
INPUT	CAN_PORT is not used (only 1 avaiable)
	Message *m pointer to message to send
OUTPUT	1 if  hardware -> CAN frame
******************************************************************************/
{
    uint32_t word0 = 0, word1 = 0, word2 = 0;
    uint32_t sid10_0 = 0, eid5_0 = 0, eid17_6 = 0;

    // Variables for setting correct TXREQ bit
    uint16_t bit_to_set;
    uint16_t offset;
    uint16_t *bufferCtrlRegAddr;

    //TODO: cancel previous message??? Don't use a buffer for transmitting (so emergency etc. works)

    // Divide the identifier into bit-chunks for storage
    // into the registers.
//    if (message->frame_type == CAN_FRAME_EXT) {
//        eid5_0 = (message->id & 0x3F);
//        eid17_6 = (message->id >> 6) & 0xFFF;
//        sid10_0 = (message->id >> 18) & 0x7FF;
//        word0 = 1;
//        word1 = eid17_6;
//    } else {
        sid10_0 = (m->cob_id & 0x7FF);
//    }

    word0 |= (sid10_0 << 2);
    word2 |= (eid5_0 << 10);

    // Set remote transmit bits
    if (m->rtr) {
        word0 |= 0x2;
        word2 |= 0x0200;
    }
    
    ecan1TXMsgBuf[0] = word0;
    ecan1TXMsgBuf[1] = word1;
    ecan1TXMsgBuf[2] = ((word2 & 0xFFF0) + m->len);
    ecan1TXMsgBuf[3] = ((uint16_t) m->data[1] << 8 | ((uint16_t) m->data[0]));
    ecan1TXMsgBuf[4] = ((uint16_t) m->data[3] << 8 | ((uint16_t) m->data[2]));
    ecan1TXMsgBuf[5] = ((uint16_t) m->data[5] << 8 | ((uint16_t) m->data[4]));
    ecan1TXMsgBuf[6] = ((uint16_t) m->data[7] << 8 | ((uint16_t) m->data[6]));

    // Set the correct transfer intialization bit (TXREQ) based on message buffer.
    //offset = message->buffer >> 1;
    //bufferCtrlRegAddr = (uint16_t *) (&C1TR01CON + offset);
    //bit_to_set = 1 << (3 | ((message->buffer & 1) << 3));
    //*bufferCtrlRegAddr |= bit_to_set;
    C1TR01CONbits.TXEN0 = 1;
    C1TR01CONbits.TX0PRI = 0;
    C1TR01CONbits.TXREQ0 = 1;
}

unsigned char canReceive(Message *m)
/******************************************************************************
The driver pass a received CAN message to the stack
INPUT	Message *m pointer to received CAN message
OUTPUT	1 if a message received
******************************************************************************/
{
    //get the first message in the queue (if any)
    if(rxbuffer_start!=rxbuffer_stop){
        m = &rxbuffer[rxbuffer_start++];
        if(rxbuffer_start>=CAN_RX_BUF_SIZE){
            rxbuffer_start = 0;
        }
        return 1;
    } else {
        return 0;
    }
}

/***************************************************************************/
char canChangeBaudRate_driver( CAN_HANDLE fd, char* baud)
{
	return 0; //not supported
}



void __attribute__((interrupt, no_auto_psv))_C1Interrupt(void)
{
    // Give us a CAN message struct to populate and use
    Message* m;
    uint8_t ide = 0;
    uint8_t srr = 0;
    uint32_t id = 0;
    uint8_t index_byte;
    uint16_t buffer;
    uint16_t *ecan_msg_buf_ptr;
    static uint8_t packet_idx;
    unsigned i;

    if (C1INTFbits.TBIF) {        
        C1INTFbits.TBIF = 0; //message was transmitted, nothing to do, I guess
    }
    // If the interrupt was fired because of a received message
    // package it all up and store in the queue.
    if (C1INTFbits.RBIF) {
        //find current message in buffer, we overwrite old messages in case the buffer overflows
        //(thus we can handle emergencies etc.)
        m = &rxbuffer[rxbuffer_stop++];
        if(rxbuffer_stop>=CAN_RX_BUF_SIZE){
            rxbuffer_stop = 0;
        }

        // Obtain the buffer the message was stored into, checking that the value is valid to refer to a buffer
        if (C1VECbits.ICODE < 32) {
            buffer = C1VECbits.ICODE;
        }

        ecan_msg_buf_ptr = ecan1RXMsgBuf[buffer];

        // Clear the buffer full status bit so more messages can be received.
        if (C1RXFUL1 & (1 << buffer)) {
            C1RXFUL1 &= ~(1 << buffer);
        }

        //  Move the message from the DMA buffer to a data structure and then push it into our circular buffer.

        // Read the first word to see the message type
        ide = ecan_msg_buf_ptr[0] & 0x0001;
        srr = ecan_msg_buf_ptr[0] & 0x0002;

        /* Format the message properly according to whether it
         * uses an extended identifier or not.
         */
        if (ide == 0) {
            m->cob_id = (uint32_t) ((ecan_msg_buf_ptr[0] & 0x1FFC) >> 2);
        } else {
            //ehm, error. only std messages supported for now
        }

        /* If message is a remote transmit request, mark it as such.
         * Otherwise it will be a regular transmission so fill its
         * payload with the relevant data.
         */
        if (srr == 1) {
            m->rtr = 1; //TODO: do we need to copy the payload??? I don't think so?
        } else {
            m->rtr = 0;

            m->len = (uint8_t) (ecan_msg_buf_ptr[2] & 0x000F);
            m->data[0] = (uint8_t) ecan_msg_buf_ptr[3];
            m->data[1] = (uint8_t) ((ecan_msg_buf_ptr[3] & 0xFF00) >> 8);
            //LED3 != LED3;//message.payload[1];
            //LED2 =  message.payload[0];
            m->data[2] = (uint8_t) ecan_msg_buf_ptr[4];
            m->data[3] = (uint8_t) ((ecan_msg_buf_ptr[4] & 0xFF00) >> 8);
            m->data[4] = (uint8_t) ecan_msg_buf_ptr[5];
            m->data[5] = (uint8_t) ((ecan_msg_buf_ptr[5] & 0xFF00) >> 8);
            m->data[6] = (uint8_t) ecan_msg_buf_ptr[6];
            m->data[7] = (uint8_t) ((ecan_msg_buf_ptr[6] & 0xFF00) >> 8);

            
        }


        // Be sure to clear the interrupt flag.
        C1RXFUL1 = 0;
        C1INTFbits.RBIF = 0;
    }

    // Clear the general ECAN1 interrupt flag.
    IFS2bits.C1IF = 0;

}