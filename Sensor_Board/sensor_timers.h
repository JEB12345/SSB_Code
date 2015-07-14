/* 
 * File:   sensor_timers.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef SENSOR_TIMERS_H
#define	SENSOR_TIMERS_H
#include "sensor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif
    return_value_t timers_init();

    /**
    * Sets up timer 4 for an event 'microseconds' in the future.
    * @param microseconds how far in the future do we need to trigger the event
    * @param cb callback function that gets called when the timer expires
    */
    void timer_4_set(uint16_t microseconds, void (*cb)());

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_TIMERS_H */

