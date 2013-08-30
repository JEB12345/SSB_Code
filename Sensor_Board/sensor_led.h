/* 
 * File:   sensor_led.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef SENSOR_LED_H
#define	SENSOR_LED_H
#include "sensor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif
    
    return_value_t led_init();
    void led_update();
    void led_rgb_set(uint8_t r, uint8_t g, uint8_t b);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_LED_H */

