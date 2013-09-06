/* 
 * File:   sensor_led.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef SENSOR_LED_H
#define	SENSOR_LED_H
#include "motor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif
    
    return_value_t led_init();
    void led_update();
    void led_intensity_set(uint8_t led1, uint8_t led2, uint8_t led3, uint8_t led4);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_LED_H */

