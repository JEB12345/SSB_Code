//#define CO_FCY 70000
//#include "CANopen.h"
//#include "sensor_state.h"
//#include "sensor_can.h"
////#include "CO_driver.h"
//
//const CO_CANbitRateData_t  CO_CANbitRateData[8] = {CO_CANbitRateDataInitializers};
//
//can_data can_state;
//CO_t* co;
//
//return_value_t can_init()
//{
//    can_state.init_return = RET_OK;
//    co = 0;
//    int err;
//    err = CO_init(&co);
//    if(err){
//        can_state.init_return = RET_ERROR;
//    } else {
//        CO_CANsetNormalMode(ADDR_CAN1);
//    }
//    return can_state.init_return;
//}
//
//unsigned can_tick()
//{
//    return CO_process(co,1);
//}

#include "sensor_state.h"
#include "sensor_can.h"
#include "../libs/CanFestival-3/include/dspic33e/can_dspic33e.h"
#include "../libs/CanFestival-3/include/dspic33e/canfestival.h"
#include "ObjDict.h"
#include <dma.h>

can_data can_state;
extern CO_Data ObjDict_Data;

static unsigned int ecan1RXMsgBuf[32][8];
static unsigned int ecan1TXMsgBuf[8];
#define CAN_RX_BUF_SIZE 5
static volatile Message rxbuffer[CAN_RX_BUF_SIZE]; //this is an internal buffer for received messages
static volatile uint8_t rxbuffer_start;
static volatile uint8_t rxbuffer_stop;
static Message* m;

return_value_t can_init()
{
    can_state.init_return = RET_OK;
    if(!canInit(1000))
    {
        //fail
        can_state.init_return = RET_ERROR;
        return can_state.init_return;
    }
    //initialize CAN timer
    setNodeId (&ObjDict_Data, 0);
    setState(&ObjDict_Data, Initialisation);	// Init the state

    return can_state.init_return;
}

uint8_t can_process()
{
    Message m_copy;
    if(canReceive(m)){
        m_copy = *m; //the packet could be overwritten in an interrupt, so copy it
        canDispatch(&ObjDict_Data, &m_copy); //send packet to CanFestival
        return 1;
    }
    else{
        return 0;
    }
}

void __attribute__((interrupt, no_auto_psv))_C1Interrupt(void)
{
    // Give us a CAN message struct to populate and use
    //Message* m;
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