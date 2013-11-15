#include "sensor_state.h"
#include <p33Exxxx.h>

    system_data system_state;
    motor_cmd_data motor_cmd_state[2];

return_value_t state_init()
{
    system_state.init_return = RET_OK;
    system_state.state = STATE_INITIALIZED;
    motor_cmd_state[0].brake = 1;
    motor_cmd_state[1].brake = 1;
    motor_cmd_state[0].vel = 0;
    motor_cmd_state[1].vel = 0;
    motor_cmd_state[0].torque = 0;
    motor_cmd_state[1].torque = 0;
    return system_state.init_return;
}

void reset_board()
{
    asm ("RESET");
    while(1);
}