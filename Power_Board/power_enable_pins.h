/* 
 * File:   power_enable_pins.h
 * Author: jonathan
 *
 * Created on March 20, 2014, 1:58 PM
 */

#ifndef POWER_ENABLE_PINS_H
#define	POWER_ENABLE_PINS_H

#include <p33Exxxx.h>
#include "power_pindef.h"
#include "power_state.h"

/**
 * @brief enable_pins_init Initalizes the Enable pins for power and motor
 *
 * @return The function will return RET_OK if inatlization completed
 */
return_value_t enable_pins_init();

#endif	/* POWER_ENABLE_PINS_H */

