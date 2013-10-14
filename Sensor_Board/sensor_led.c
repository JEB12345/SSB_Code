#include "p33Exxxx.h"
#include "sensor_pindefs.h"
#include "sensor_led.h"
#include "sensor_state.h"

led_data led_state;
static uint8_t RGB_LED_ON = 1;

return_value_t led_init()
{
    led_state.rgb_blue = 0;
    led_state.rgb_green = 0;
    led_state.rgb_red = 0;
    LED_1 = 0;
    LED_2 = 0;
    LED_3 = 0;
    LED_4 = 0;
    RGB_BLUE = 1;
    RGB_RED = 1;
    RGB_GREEN = 1;
    led_state.init_return = RET_OK;
    return led_state.init_return;
}

/**
 * This function is called by the main loop and
 */
void led_update()
{
    static uint16_t state = 0;

    if(RGB_LED_ON == 1){
        RGB_RED = led_state.rgb_red<state;
        RGB_GREEN =led_state.rgb_green<state;
        RGB_BLUE = led_state.rgb_blue<state;

        if(++state>=8){
            state=0;
        }
    }
}

/**
 * Sets the color of the RGB led. Values between 0 to 255 (internally downscaled).
 * @param r
 * @param g
 * @param b
 */
void led_rgb_set(uint8_t r, uint8_t g, uint8_t b)
{
    led_rgb_on();
    led_state.rgb_red = r>>5;
    led_state.rgb_green = g>>5;
    led_state.rgb_blue = b>>5;
}

void led_rgb_off()
{
    RGB_RED = 1;
    RGB_BLUE = 1;
    RGB_GREEN = 1;

    RGB_LED_ON = 0;
}

void led_rgb_on()
{
    RGB_RED = 0;
    RGB_BLUE = 0;
    RGB_GREEN = 0;
    
    RGB_LED_ON = 1;
}
