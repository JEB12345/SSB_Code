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

    /**
     * @brief led_init Initalizes the LEDs to zero
     *
     * @return The function will return RET_OK if inatlization completed
     */
    return_value_t led_init();

    /**
     * @brief led_update Updates the state of the RGB LED
     *
     */
    void led_update();

    /**
     * @brief led_rgb_set Sets the individual LEDs of the RGB to the given values
     *
     * @param r Red LED
     * @param g Green LED
     * @param b Blue LED
     */
    void led_rgb_set(uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief led_rgb_off Turns off the RGB LED, disables led_update
     *
     */
    void led_rgb_off();

    /**
     * @brief led_rgb_on Turns on the RGB LED and enables led_update
     *
     */
    void led_rgb_on();
    
#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_LED_H */

