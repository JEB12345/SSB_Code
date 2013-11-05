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
    return_value_t can_init();
    //unsigned can_tick();
    uint8_t can_process();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_CAN_H */

