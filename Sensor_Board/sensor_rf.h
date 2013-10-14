/* 
 * File:   sensor_rf.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef SENSOR_RF_H
#define	SENSOR_RF_H
#include "sensor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif
#define XBEE_RESET_RETRIES  5 //how many times to try to reset the XBEE before failing
#define XBEE_RESET_WAIT_CYCLES  100000 //how many cycles to wait before the current XBEE reset trial has failed
    return_value_t rf_init();

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
     * 
     * @return The function returns error if it is unable to allocate the correct amount of memory, else success
     */
    return_value_t xbee_at_cmd(const char *atxx, const uint8_t *parmval, int parmlen, bool queued, xbee_at_packet_t* at_data);

    /**
     * This function evaluates the pending callbacks.
     * This function has to be called at a fixed rate (ms specifies the number of milliseconds since the last call).
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

