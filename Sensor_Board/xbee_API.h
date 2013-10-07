/* 
 * File:   xbee_API.h
 * Author: jonathan
 *
 * Created on October 1, 2013, 8:14 PM
 */

#ifndef XBEE_API_H
#define	XBEE_API_H

#include "sensor_state.h"
#include "sensor_pindefs.h"
#include "sensor_rf.h"

/****************************
 * API Frame Names and Values
 ****************************/
#define Tx64_Request 0x00
#define AT_Command 0x08
#define AT_Command_QPV 0x09
#define Remote_Command_Request 0x07
#define TX_IPv4 0x20
#define Rx64_Inidcator 0x80
#define AT_Command_Response 0x88
#define TX_Status 0x89
#define Modem_Status 0x8A
#define IO_Data_Sample_Rx 0x8F
#define Remote_Command_Response 0x87
#define RX_IPv4 0xB0

#define checksum_value 0xFF

/************************************
 * Struct to contain the wifi packets
 ************************************/
typedef struct {
    uint8_t     Length;     // Length of Data Frame not including checksum
    uint8_t     Frame_Name; // Type of message Defined in the header
    uint32_t    cmdData;    // Frame data, size dependent on the frame type
    uint8_t     checksum;   // Checksum defined as 0xFF = Frame_Name+cmdDtat+checksum
}wifi_data;

/***********
 * Functions
 ***********/

/**
 * @brief confirm_checksum checks if message was received correctly.
 *
 * Checks the integrity of the message. If the checksum does not equal 0xFF, the
 * fuction will return RET_ERROR.
 *
 * @param data A pointer to the wifi_data being checked
 */
return_value_t confirm_checksum(wifi_data* data);



#endif	/* XBEE_API_H */

