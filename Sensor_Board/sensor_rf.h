/* 
 * File:   sensor_rf.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef SENSOR_RF_H
#define	SENSOR_RF_H
#include "sensor_state.h"
#include "xbee_API.h"
#ifdef	__cplusplus
extern "C" {
#endif
#define XBEE_RESET_RETRIES  5 //how many times to try to reset the XBEE before failing
#define XBEE_RESET_WAIT_CYCLES  100000 //how many cycles to wait before the current XBEE reset trial has failed
    return_value_t rf_init();

    /**
     * Defines the starting values for the network_data struct
     */
    return_value_t network_init();

    /**
     * @brief xbee_at_cmd Create the raw AT packet based on the user command and input parameters
     *
     * The user will input the AT command idenifier based on the XBee Wifi data sheet
     * as well as any associated values with the ID. The function will then allocate
     * memory for the packet, fill in the memory, and pass the pointer to at_data.
     *
     * @param *atxx A pointer to the AT Command ID
     * @param *parmval A pointer to the parameter the user is sending 
     * @param parmlen The length of the parameter in bytes
     * @param queued A boolean stating if the use wants to send this as an AT Command
     *        or an AT Queued command
     * @param at_data A pointer to the xbee_at_packet_t where the user wants to call the raw packet for transfer
     * @param transmitted_cb callback for when the packet was sent over SPI to the Xbee module
     * @param response_cb callback for when we received a matching AT cmd response packet
     * @param timeout timeout (in ms) for the AT cmd response callback (set to 0 to disable callback)
     *
     * @return The function returns error if it is unable to allocate the correct amount of memory, else success
     */
    return_value_t xbee_at_cmd(const char *atxx, const uint8_t *parmval, int parmlen, bool queued, xbee_at_packet_t* at_data, XBEE_TRANSMITTED_CB, XBEE_RESPONSE_CB, uint16_t timeout);

    /**
     * See xbee_at_cmd.
     * Same function, but without callbacks.
     */
    return_value_t xbee_at_cmd_no_cb(const char *atxx, const uint8_t *parmval, int parmlen, bool queued, xbee_at_packet_t* at_data);

    /**
     * Allocates the data array for an IP packet.
     * The callbacks are also initialized (to NULL).
     * @param allocateAmount desired number of bytes for the IP payload
     * @param ip_data the IP packet to initialize
     * @return RET_OK if the array could be allocated, else RET_ERROR
     */
    return_value_t allocate_ip_packet(uint16_t allocateAmount, xbee_tx_ip_packet_t* ip_data);

    /**
     * Schedules an IP packet for transmission by adding it to the cyclic buffer.
     * The data array will be automatically freed after transmission.
     * @param ip_data the IP packet to transmit
     * @return RET_OK if the packet was successfully added to the transmit buffer, else RET_ERROR
     */
    return_value_t transmit_ip_packet(xbee_tx_ip_packet_t* ip_data);


    /**
     * returns a pointer to the actual parameter data (if any) in an AT cmd response packet
     * @param _X
     */
    #define xbee_at_cmd_data(_X)    ((_X)+8)

    /**
     * returns a pointer to the actual IP packet data (if any) in an IPv4 RX frame
     * @param _X
     */
    #define xbee_ip_rx_rf_data(_X)    ((_X)+14)

    #define xbee_ip_rx_rf_data_len(_X) ((*(_X)).length-15)

    /**
     * Start transmission of the current AT command
     */
    #define xbee_send_at_cmd() (rf_state.xbee_at_req=1)

    /**
<<<<<<< HEAD
     *@brief xbee_at_rawdata_size This function takes any full length raw AT command packet of and returns the size of the data
     *
     * @param _X raw AT command packet
     */
    #define xbee_at_rawdata_size(_X)   (sizeof(_X)-LENGTH_XBEE_AT_FRAME_NOPARAM)

    /**
     *@brief xbee_ip_rawdata_size This function takes any full length raw IPv4 command packet of and returns the size of the data
     *
     * @param _X raw IPv4 command packet
     */
    #define xbee_ip_rawdata_size(_X)   (sizeof(_X)-LENGTH_XBEE_IPv4_FRAME_NODATA)

    /* Registers a packet handler for received IP packets
     * A packet handler will be called when there is data in the IP RX buffer.
     * If the packet handler returns true, we assume that the data was handled (and freed by the packet handler if necessary).
     * If the packet handler returns false, the packet is passed onto the next packet handler.
     * In case all handlers return false, the packet is freed if necessary.
     * @param ip_rx_pkt_handler function pointer to the packet handler to register
     */
    void rf_add_ip_rx_packet_handler(bool (*ip_rx_pkt_handler)(xbee_rx_ip_packet_t*));

    /**
     * This function evaluates the pending callbacks.
     * This function has to be called at a fixed rate (ms specifies the number of milliseconds since the last call).
     * @param ms milliseconds since the last time this function was called
     */
    void rf_tick(unsigned ms);

    /**
     * This function updates the XBEE state machine and processes incoming and outgoing data.
     * It is a non-blocking function that has to be called as often as possible to ensure smooth operation.
     * However, it does not need to be called at a fixed rate (cf. rf_tick).
     */
    void rf_process();


#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_RF_H */

