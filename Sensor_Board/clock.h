/* 
 * File:   sensor_clock.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:54 PM
 */

#ifndef SENSOR_CLOCK_H
#define	SENSOR_CLOCK_H
#ifdef	__cplusplus
extern "C" {
#endif

    #include "sensor_state.h"

    /**
     * @brief clock_init() Initalizes the dspic33E clock to 70Mips or 70MHz
     *
     * @return The function will return RET_OK if inatlization completed
     */
    return_value_t clock_init();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_CLOCK_H */

