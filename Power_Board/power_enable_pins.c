#include "power_enable_pins.h"

return_value_t enable_pins_init() {
    //Power and Motor Control Pins Init
    EN_BACKUP_5V5 =     1;//ENABLED
    EN_MAIN_5V5 =       0;//DISABLED
    EN_24V_5V5_IC =     0;//DISABLED
    BACKUP_CHARGE_EN =  1;//DISABLED -- Inverted Logic
    MOTOR_EN =          0;//DISABLED
    EN_MOTOR_CURRENT =  0;//DISABLED
    G_BAT_PIC =         0;//DISABLED
    G_BAT_KILL =        0;//DISABLED

    //5V5 Output Control Pins Init
    EN_OUT_1 =  0;//DISABLED
    EN_OUT_2 =  0;//DISABLED
    EN_OUT_3 =  0;//DISABLED
    EN_OUT_4 =  0;//DISABLED

    return RET_OK;
}
