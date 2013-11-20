#include "sensor_state.h"
#include <p33Exxxx.h>

    system_data system_state;
    motor_cmd_data motor_cmd_state[2];

return_value_t state_init()
{
    int i;
    system_state.init_return = RET_OK;
    system_state.state = STATE_INITIALIZED;
    for(i=0;i<2;++i){
        motor_cmd_state[i].brake = 1;
        motor_cmd_state[i].vel = 0;
        motor_cmd_state[i].torque = 0;
        motor_cmd_state[i].coast = 0;
        motor_cmd_state[i].mode = 0;
        motor_cmd_state[i].p = 1;
        motor_cmd_state[i].i = 1;
        motor_cmd_state[i].d = 1;
        motor_cmd_state[i].position = 0;
    }
    return system_state.init_return;
}

void reset_board()
{
    asm ("RESET");
    while(1);
}