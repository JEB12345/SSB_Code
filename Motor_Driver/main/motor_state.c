#include "motor_state.h"

    system_data system_state;
    motor_data  motor_state;

return_value_t state_init()
{
    system_state.init_return = RET_OK;
    system_state.state = STATE_INITIALIZED;
    system_state.ticks_since_last_cmd = 0;
    motor_state.rotor_position = 0x0;
    motor_state.rotor_turns = 0x1FFF;
    return system_state.init_return;
}
