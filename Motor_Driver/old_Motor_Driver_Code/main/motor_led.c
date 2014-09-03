#include "p33Exxxx.h"
#include "motor_pindefs.h"
#include "motor_led.h"
#include "motor_state.h"

led_data led_state;

return_value_t led_init()
{
    unsigned i;
    for(i=0; i<4;++i)
        led_state.led_intensities[i] = 0;
    
    led_state.init_return = RET_OK;
    return led_state.init_return;
}

/**
 * This function is called by the main loop and
 */
void led_update()
{
    static uint16_t state = 0;

    LED1 = led_state.led_intensities[0]>state;
    LED2 = led_state.led_intensities[1]>state;
    LED3 = led_state.led_intensities[2]>state;
    LED4 = led_state.led_intensities[3]>state;

    if(++state>16){
        state=0;
    }
}

/**
 * Sets the intensity of the status leds. Values between 0 to 255 (internally downscaled).
 */
void led_intensity_set(uint8_t led1, uint8_t led2, uint8_t led3, uint8_t led4)
{
    led_state.led_intensities[0] = led1>>4;
    led_state.led_intensities[1] = led2>>4;
    led_state.led_intensities[2] = led3>>4;
    led_state.led_intensities[3] = led4>>4;
}