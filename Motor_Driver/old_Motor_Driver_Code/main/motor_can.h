/* 
 * File:   sensor_can.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef SENSOR_CAN_H
#define	SENSOR_CAN_H
#include "motor_state.h"
#include "superball_communication.h"
#ifdef	__cplusplus
extern "C" {
#endif
 //   return_value_t can_init();

//    return_value_t can_transmit_packet(superball_packet* packet);

    //below is private

    // Message Types either a data message or a remote transmit request
enum can_msg_type {
	CAN_MSG_DATA = 0,
	CAN_MSG_RTR
};

// CAN frame type: either extended (29-bit header) or standard (11-bit header)
enum can_frame_type {
	CAN_FRAME_EXT = 0,
	CAN_FRAME_STD
};

// Data structures
typedef struct {
	uint32_t id;           // The 11-bit or 29-bit message ID
	uint8_t  buffer;       // An internal-use variable referring to buffer this message was received into/sent from.
	uint8_t  message_type; // The message type. See can_msg_type.
	uint8_t  frame_type;   // The frame type. See can_frame_type.
	uint8_t  payload[8];   // The message payload. Stores between 0 and 8 bytes of data.
	uint8_t  validBytes;   // Indicates how many bytes are valid within payload.
} tCanMessage;

typedef union {
	tCanMessage message;
	uint8_t     bytes[sizeof(tCanMessage)];
} CanUnion;

return_value_t can_transmit_packet(superball_packet* packet, uint16_t can_id);
return_value_t can_init();

/**
 * This function initializes the first ECAN module. It takes a parameters array
 * of uint16s to specify all of the options.
 *
 * The parameters array is used as follows:
 * parameters[0] = bits 0-1: specify standard or extended frames (1 for standard, 2 for extended, 0 means ECAN is not used),
 *                 bits 2-4: specify module mode (loopback, disabled, etc.),
 *                 bits 5-7: specify which DMA channel to use for receiving,
 *                 bits 8-10: specify which DMA channel to use for transmitting
 * parameters[1] = bit rate in units of hundreds of bits per second
 * parameters[2] = oscillator frequency in 10000s of Hertz
 * parameters[3] = bits 0-2: phase segment 1
 *                 bits 3-5: propagation delay
 *                 bits 6-8: phase segment 2
 *                 bits 9-10: sync jump width
 *                 bit 11: specifies triple sample at sampling point
 * parameters[4] = filters 0 through 15 enable
 * parameters[5] = filters 0 through 7 mask select
 * parameters[6] = filters 8 through 15 mask select
 * parameters[7] = mask 0 (standard, exide, eid17-16)
 * parameters[8] = mask 0 (eid15-0)
 * parameters[9] = mask 1 (standard, exide, eid17-16)
 * parameters[10] = mask 1 (eid15-0)
 * parameters[11] = mask 2 (standard, exide, eid17-16)
 * parameters[12] = mask 2 (eid15-0)
 * parameters[13] = C1TR01CON
 * parameters[14] = C1TR23CON
 * parameters[15] = C1TR45CON
 * parameters[16] = C1TR67CON
 * parameters[17] = Buffer pointer for filters 0-3
 * parameters[18] = Buffer pointer for filters 4-7
 * parameters[19] = Buffer pointer for filters 8-11
 * parameters[20] = Buffer pointer for filters 12-15
 * parameters[21] = filter 0 (standard, exide, eid17-16)
 * parameters[22] = filter 0 (extended 15-0)
 * parameters[23] = filter 1 (standard, exide, eid17-16)
 * parameters[24] = filter 1 (extended 15-0)
 * parameters[25] = filter 2 (standard, exide, eid17-16)
 * parameters[26] = filter 2 (extended 15-0)
 * parameters[27] = filter 3 (standard, exide, eid17-16)
 * parameters[28] = filter 3 (extended 15-0)
 * parameters[29] = filter 4 (standard, exide, eid17-16)
 * parameters[30] = filter 4 (extended 15-0)
 * parameters[31] = filter 5 (standard, exide, eid17-16)
 * parameters[32] = filter 5 (extended 15-0)
 * parameters[33] = filter 6 (standard, exide, eid17-16)
 * parameters[34] = filter 6 (extended 15-0)
 * parameters[35] = filter 7 (standard, exide, eid17-16)
 * parameters[36] = filter 7 (extended 15-0)
 * parameters[37] = filter 8 (standard, exide, eid17-16)
 * parameters[38] = filter 8 (extended 15-0)
 * parameters[39] = filter 9 (standard, exide, eid17-16)
 * parameters[40] = filter 9 (extended 15-0)
 * parameters[41] = filter 10 (standard, exide, eid17-16)
 * parameters[42] = filter 10 (extended 15-0)
 * parameters[43] = filter 11 (standard, exide, eid17-16)
 * parameters[44] = filter 11 (extended 15-0)
 * parameters[45] = filter 12 (standard, exide, eid17-16)
 * parameters[46] = filter 12 (extended 15-0)
 * parameters[47] = filter 13 (standard, exide, eid17-16)
 * parameters[48] = filter 13 (extended 15-0)
 * parameters[49] = filter 14 (standard, exide, eid17-16)
 * parameters[50] = filter 14 (extended 15-0)
 * parameters[51] = filter 15 (standard, exide, eid17-16)
 * parameters[52] = filter 15 (extended 15-0)
 */
void ecan1_init(const uint16_t *parameters);

/**
 * Pops the top message from the ECAN1 reception buffer.
 * @return A tCanMessage struct with the older message data.
 */
int ecan1_receive(tCanMessage *msg, uint8_t *messagesLeft);


/**
 * This function transmits a CAN message on the ECAN1 CAN bus.
 * This function shouldn't be used directly, use buffered_transmit
 * instead.
 */
void ecan1_transmit(const tCanMessage *message);

/**
 * Transmits a CAN message via a circular buffer interface
 * similar to that used by CAN message reception.
 */
void ecan1_buffered_transmit(const tCanMessage *message);

/**
 * This function provides a general way to initialize the DMA peripheral.
 *
 * parameters[0] = IRQ address & squeezed version of DMAxCON minus CHEN bit
 * parameters[1] = address of peripheral (DMAxPAD)
 * parameters[2] = Number of memory units per DMA packet, starting at 1(DMAxCNT)
 * parameters[3] = Primary DPSRAM start address offset bits (DMAxSTA)
 * parameters[4] = Which DMA channel to configure
 * parameters[5] = Secondary DPSRAM start address offset bits (DMAxSTB)
 */
void can_dma_init(const uint16_t *parameters);

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_CAN_H */

