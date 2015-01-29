/* 
 * File:   power_temperature.h
 * Author: ken
 *
 * Created on January 28, 2015, 11:04 PM
 */

#ifndef POWER_TEMPERATURE_H
#define	POWER_TEMPERATURE_H
#include "power_state.h"

#ifdef	__cplusplus
extern "C" {
#endif

    return_value_t temperature_init();

    /**
     * Starts an I2C temperature reading operation.
     * Call this function regularly to update the temperature state.
     * @return RET_OK if the I2C buffer wasn't full, else RET_ERROR
     */
    return_value_t temperature_update();

#ifdef	__cplusplus
}
#endif

#endif	/* POWER_TEMPERATURE_H */

