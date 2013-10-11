#define CO_FCY 70000
#include "CANopen.h"
#include "sensor_state.h"
#include "sensor_can.h"
//#include "CO_driver.h"

const CO_CANbitRateData_t  CO_CANbitRateData[8] = {CO_CANbitRateDataInitializers};

can_data can_state;
CO_t* co;

return_value_t can_init()
{
    can_state.init_return = RET_OK;
    co = 0;
    int err;
    err = CO_init(&co);
    if(err){
        can_state.init_return = RET_ERROR;
    } else {
        CO_CANsetNormalMode(ADDR_CAN1);
    }
    return can_state.init_return;
}

unsigned can_tick()
{
    return CO_process(co,1);
}