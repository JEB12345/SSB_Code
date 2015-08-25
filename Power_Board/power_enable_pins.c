#include "power_enable_pins.h"

return_value_t enable_pins_init() {
    //Power and Motor Control Pins Init
    EN_BACKUP_5V5 =     1;//ENABLED
    EN_VBAT_5V5   =     0;//DISABLED
    VBAT_5V5_EN   =     1;//DISABLED, Controls the Buck Converter
    KILLSWITCH_uC =     0;//DISABLED
    EN_MOTOR_CURRENT =  0;//DISABLED

    //5V5 Output Control Pins Init
    EN_OUT_1 =  0;//DISABLED
    EN_OUT_2 =  0;//DISABLED
    EN_OUT_3 =  0;//DISABLED
    EN_OUT_4 =  0;//DISABLED

    return RET_OK;
}
