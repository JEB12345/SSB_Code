#include "power_led.h"
#include "p33Exxxx.h"
#include "power_state.h"

return_value_t led_init() {

    // RGB LED is off when high, on when low.
    LED_R = 1;
    LED_G = 1;
    LED_B = 1;

    // Setting the status LED shouldn't actually matter, since
    // it gets reset in the main loop anyway depending on the
    // battery state, so this is mostly for thoroughness' sake.
    LED_STATUS = 0;

    return RET_OK;
}
