#include "power_led.h"
#include "p33Exxxx.h"
#include "power_state.h"

return_value_t led_init() {
    LED_1 = 0;
    LED_2 = 0;
    LED_3 = 0;
    LED_STATUS = 0;

    return RET_OK;
}