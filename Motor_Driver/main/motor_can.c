#include "motor_state.h"
#include "motor_can.h"
#include "p33Exxxx.h"
#include "motor_pindefs.h"
#include "superball_communication.h"
#include <dma.h>

// Specify the number of 8-byte CAN messages buffer supports.
// This can be overridden by user code.
#ifndef ECAN1_BUFFERSIZE
#define ECAN1_BUFFERSIZE 16*50 //8 * 24
#endif

unsigned int ecan1RXMsgBuf[32][8] __attribute__((aligned(32 * 16)));
unsigned int ecan1TXMsgBuf[32][8] __attribute__((aligned(32 * 16)));

//TODO: move all of this into a state struct
// Initialize our circular buffers and data arrays for transreceiving CAN messages
CircularBuffer ecan1_rx_buffer;
uint8_t rx_data_array[ECAN1_BUFFERSIZE];
CircularBuffer ecan1_tx_buffer;
uint8_t tx_data_array[ECAN1_BUFFERSIZE];

// Track whether or not we're currently transmitting
unsigned char currentlyTransmitting = 0;
unsigned char receivedMessagesPending = 0;

return_value_t can_init()
{
    unsigned int config;
    unsigned int irq;
    unsigned long int stb_address;
    unsigned int pad_address;
    unsigned int count;
    // 0 normal, 1 disable, 2 loopback, 3 listen-only, 4 configuration, 7 listen all messages
    uint8_t desired_mode = 0;//(parameters[0] & 0x001C) >> 2;

    //CONFIG CAN
    // Make sure the ECAN module is in configuration mode.
    // It should be this way after a hardware reset, but
    // we make sure anyways.
    C1CTRL1bits.REQOP = 4;
    while (C1CTRL1bits.OPMODE != 4);

    //1Mbaud
    C1CFG1bits.BRP = 32;//4 //TQ= FCAN/10 = 14Mhz = 14 TQ/bit
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
    IEC0bits.DMA0IE = 1; // Enable DMA Channel 0 interrupt
    DMA0CONbits.CHEN = 1; // Enable DMA Channel 0
    pad_address = (volatile unsigned int)&C1RXD;
    stb_address = 0x0;
    OpenDMA0( config, irq, (long unsigned int)ecan1RXMsgBuf,
        stb_address,pad_address, count );
    
    
    // Setup message filters and masks.
    C1CTRL1bits.WIN = 1; // Allow configuration of masks and filters

    C1FMSKSEL1bits.F0MSK=0x0; //Filter 0 will use mask 0
    C1RXM0SIDbits.SID = 0b11111111111; //Set mask
    C1RXF0SIDbits.SID = 0x1; //set filter
    C1RXM0SIDbits.MIDE = 0x0; //only receive standard frames
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
}

return_value_t can_transmit_packet(superball_packet* packet)
{
    tCanMessage msg;
    unsigned i;
    msg.id = 1;
    msg.frame_type = CAN_FRAME_STD;
    msg.message_type = CAN_MSG_DATA;
    msg.validBytes = 8;
    for(i=0;i<8;++i)
        msg.payload[i] = i+1;
    ecan1_buffered_transmit(&msg);
    while(1){
        if(!currentlyTransmitting){
            msg.payload[2]+=1;
            ecan1_buffered_transmit(&msg);
            LED1 = !LED1;
        }
    }
    /*
    ecan1TXMsgBuf[0][0] = 0x123C;
    ecan1TXMsgBuf[0][1] = 0x0000;
    ecan1TXMsgBuf[0][2] = 0x0008;
    ecan1TXMsgBuf[0][3] = 0x1;
    ecan1TXMsgBuf[0][4] = 0x2;
    ecan1TXMsgBuf[0][5] = 0x3;
    ecan1TXMsgBuf[0][6] = 0xabcd;
    //LED2_ON;
    C1TR01CONbits.TXREQ0 = 0x1;
    //while(C1TR01CONbits.TXREQ0 == 1){
    //}*/
}





int ecan1_receive(tCanMessage *msg, uint8_t *messagesLeft)
{
    int foundOne = CB_ReadMany(&ecan1_rx_buffer, msg, sizeof(tCanMessage));

    if (messagesLeft) {
        if (foundOne) {
            *messagesLeft = --receivedMessagesPending;
        } else {
            *messagesLeft = 0;
        }
    }

    return foundOne;
}


// NOTE: We do not block for message transmission to complete. Message queuing
// is handled by the transmission circular buffer.

void ecan1_transmit(const tCanMessage *message)
{
    uint32_t word0 = 0, word1 = 0, word2 = 0;
    uint32_t sid10_0 = 0, eid5_0 = 0, eid17_6 = 0;
    uint16_t *ecan_msg_buf_ptr = ecan1TXMsgBuf[0];//message->buffer];

    // Variables for setting correct TXREQ bit
    uint16_t bit_to_set;
    uint16_t offset;
    uint16_t *bufferCtrlRegAddr;

    // Divide the identifier into bit-chunks for storage
    // into the registers.
    if (message->frame_type == CAN_FRAME_EXT) {
        eid5_0 = (message->id & 0x3F);
        eid17_6 = (message->id >> 6) & 0xFFF;
        sid10_0 = (message->id >> 18) & 0x7FF;
        word0 = 1;
        word1 = eid17_6;
    } else {
        sid10_0 = (message->id & 0x7FF);
    }

    word0 |= (sid10_0 << 2);
    word2 |= (eid5_0 << 10);

    // Set remote transmit bits
    if (message->message_type == CAN_MSG_RTR) {
        word0 |= 0x2;
        word2 |= 0x0200;
    }

    ecan_msg_buf_ptr[0] = word0;
    ecan_msg_buf_ptr[1] = word1;
    ecan_msg_buf_ptr[2] = ((word2 & 0xFFF0) + message->validBytes);
    ecan_msg_buf_ptr[3] = ((uint16_t) message->payload[1] << 8 | ((uint16_t) message->payload[0]));
    ecan_msg_buf_ptr[4] = ((uint16_t) message->payload[3] << 8 | ((uint16_t) message->payload[2]));
    ecan_msg_buf_ptr[5] = ((uint16_t) message->payload[5] << 8 | ((uint16_t) message->payload[4]));
    ecan_msg_buf_ptr[6] = ((uint16_t) message->payload[7] << 8 | ((uint16_t) message->payload[6]));

    // Set the correct transfer intialization bit (TXREQ) based on message buffer.
    //offset = message->buffer >> 1;
    //bufferCtrlRegAddr = (uint16_t *) (&C1TR01CON + offset);
    //bit_to_set = 1 << (3 | ((message->buffer & 1) << 3));
    //*bufferCtrlRegAddr |= bit_to_set;
    C1TR01CONbits.TXEN0 = 1;
    C1TR01CONbits.TX0PRI = 0;
    C1TR01CONbits.TXREQ0 = 1;

    // Keep track of whether we're in a transmission train or not.
    currentlyTransmitting = 1;
}

/**
 * Transmits a tCanMessage using the transmission circular buffer.
 */
void ecan1_buffered_transmit(const tCanMessage *msg)
{
    if(msg->id==100)
    LATBbits.LATB7= !LATBbits.LATB7;

    // Append the message to the queue.
    // Message are only removed upon successful transmission.
    // They will be overwritten by newer message overflowing
    // the circular buffer however.
    CB_WriteMany(&ecan1_tx_buffer, msg, sizeof(tCanMessage), 1);

    // If this is the only message in the queue, attempt to
    // transmit it.
    if (!currentlyTransmitting) {
        ecan1_transmit(msg);
    }
}



void dma_init(const uint16_t *parameters)
{
    
}

/**
 * This is an interrupt handler for the ECAN1 peripheral.
 * It clears interrupt bits and pushes received message into
 * the circular buffer.
 */
void __attribute__((interrupt, no_auto_psv))_C1Interrupt(void)
{
    // Give us a CAN message struct to populate and use
    tCanMessage message;
    uint8_t ide = 0;
    uint8_t srr = 0;
    uint32_t id = 0;
    uint16_t *ecan_msg_buf_ptr;
     LED2 = !LED2;
    //LATCbits.LATC13 = 1;//!LATCbits.LATC13;
    // If the interrupt was set because of a transmit, check to
    // see if more messages are in the circular buffer and start
    // transmitting them.
    if (C1INTFbits.TBIF) {
        LED3 = !LED3;
        // After a successfully sent message, there should be at least
        // one message in the queue, so pop it off.
        CB_ReadMany(&ecan1_tx_buffer, &message, sizeof(tCanMessage));

        // Check for a buffer overflow. Then clear the entire buffer if there was.
        if (ecan1_tx_buffer.overflowCount) {
            CB_Init(&ecan1_tx_buffer, tx_data_array, ECAN1_BUFFERSIZE);
        }

        // Now if there's still a message left in the buffer,
        // try to transmit it.
        if (ecan1_tx_buffer.dataSize >= sizeof(tCanMessage)) {
            tCanMessage msg;
            CB_PeekMany(&ecan1_tx_buffer, &msg, sizeof(tCanMessage));
            ecan1_transmit(&msg);
        } else {
            currentlyTransmitting = 0;
        }

        C1INTFbits.TBIF = 0;
    }

    // If the interrupt was fired because of a received message
    // package it all up and store in the circular buffer.
    if (C1INTFbits.RBIF) {
        LED4 = !LED4;
        LED1 = 1;
        // Obtain the buffer the message was stored into, checking that the value is valid to refer to a buffer
        if (C1VECbits.ICODE < 32) {
            message.buffer = C1VECbits.ICODE;
        }

        ecan_msg_buf_ptr = ecan1RXMsgBuf[message.buffer];

        // Clear the buffer full status bit so more messages can be received.
        if (C1RXFUL1 & (1 << message.buffer)) {
            C1RXFUL1 &= ~(1 << message.buffer);
        }

        //  Move the message from the DMA buffer to a data structure and then push it into our circular buffer.

        // Read the first word to see the message type
        ide = ecan_msg_buf_ptr[0] & 0x0001;
        srr = ecan_msg_buf_ptr[0] & 0x0002;

        /* Format the message properly according to whether it
         * uses an extended identifier or not.
         */
        if (ide == 0) {
            message.frame_type = CAN_FRAME_STD;

            message.id = (uint32_t) ((ecan_msg_buf_ptr[0] & 0x1FFC) >> 2);
        } else {
            message.frame_type = CAN_FRAME_EXT;

            id = ecan_msg_buf_ptr[0] & 0x1FFC;
            message.id = id << 16;
            id = ecan_msg_buf_ptr[1] & 0x0FFF;
            message.id |= id << 6;
            id = ecan_msg_buf_ptr[2] & 0xFC00;
            message.id |= id >> 10;
        }

        /* If message is a remote transmit request, mark it as such.
         * Otherwise it will be a regular transmission so fill its
         * payload with the relevant data.
         */
        if (srr == 1) {
            message.message_type = CAN_MSG_RTR;
        } else {
            message.message_type = CAN_MSG_DATA;

            message.validBytes = (uint8_t) (ecan_msg_buf_ptr[2] & 0x000F);
            message.payload[0] = (uint8_t) ecan_msg_buf_ptr[3];
            message.payload[1] = (uint8_t) ((ecan_msg_buf_ptr[3] & 0xFF00) >> 8);
            message.payload[2] = (uint8_t) ecan_msg_buf_ptr[4];
            message.payload[3] = (uint8_t) ((ecan_msg_buf_ptr[4] & 0xFF00) >> 8);
            message.payload[4] = (uint8_t) ecan_msg_buf_ptr[5];
            message.payload[5] = (uint8_t) ((ecan_msg_buf_ptr[5] & 0xFF00) >> 8);
            message.payload[6] = (uint8_t) ecan_msg_buf_ptr[6];
            message.payload[7] = (uint8_t) ((ecan_msg_buf_ptr[6] & 0xFF00) >> 8);
        }

        // Store the message in the buffer
        CB_WriteMany(&ecan1_rx_buffer, &message, sizeof(tCanMessage), 1);

           
        // Increase the number of messages stored in the buffer
        ++receivedMessagesPending;

        // Be sure to clear the interrupt flag.
        C1INTFbits.RBIF = 0;
    }

    // Clear the general ECAN1 interrupt flag.
    IFS2bits.C1IF = 0;

}