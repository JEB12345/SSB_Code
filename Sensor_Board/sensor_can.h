/* 
 * File:   sensor_can.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef SENSOR_CAN_H
#define	SENSOR_CAN_H
#include "sensor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif

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

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_CAN_H */

