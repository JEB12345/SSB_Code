/* 
 * File:   power_can.h
 * Author: ken/Jonathan
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef POWER_CAN_H
#define	POWER_CAN_H
#include "power_state.h"
//#ifdef CONF73
//#include "power_objdict_73.h"
//#define CO(_X) power73_ ## _X
//#else
//#include "power_objdict_3.h"
//#define CO(_X) power3_ ## _X
//#endif
#include "power_objdict_include.h"

#ifdef	__cplusplus
extern "C" {
#endif

    #define CAN_PUSH_UPDATE_TIME 50

    /**
     * @brief can_init() Initalizes the dspic33e's CAN Bus at 1Mbaud
     *
     * The user will call this at the initalization of the uC to setup the
     * CAN Bus
     *
     * @return The function will return an error if initalization failed.
     */
    return_value_t can_init();

    /**
     * @brief can_process() checks to see if there is a message, if so push it
     * to CanFestival for processing
     *
     * The user will call this function either in a timed loop or non-timed 
     * loop. It will push any CAN messages in 
     *
     * @return This will return 1 if there was a received message.
     */
    uint8_t can_process();

    /**
     * @brief can_reset_node() sends an NMT CANopen reset message to a node (or to the whole network).
     * This will cause the target node to do a full reset.
     *
     * @param nodeId: id of the node to reset, or 0 to reset all slave boards
     */
    void can_reset_node(uint8_t nodeId);

    /**
     * @brief can_start_node() sends an NMT CANopen start message to a node (or to the whole network).
     * This will cause the target node to do a go from pre-operational to operational mode or do nothing in case it is already in operational mode.
     *
     * @param nodeId: id of the node to start, or 0 to start all slave boards
     */
    void can_start_node(uint8_t nodeId);

    /**
     * @brief Call this function when the CAN timer has expired.
     */
    void can_time_dispatch();

    void can_push_state();

    void can_update();

#ifdef	__cplusplus
}
#endif

#endif	/* POWER_CAN_H */

