#include "power_state.h"
#include <p33Exxxx.h>

system_data system_state;

return_value_t state_init()
{
    system_state.init_return = RET_OK;
    system_state.state = STATE_INITIALIZED;

    return system_state.init_return;
}

void reset_board()
{
    asm ("RESET");
    while(1);
}