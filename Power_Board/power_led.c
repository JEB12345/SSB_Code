#include "power_led.h"
#include "p33Exxxx.h"
#include "power_state.h"

return_value_t led_init() {
    LED_R = 0;
    LED_G = 0;
    LED_B = 0;
    LED_STATUS = 0;

    return RET_OK;
}
