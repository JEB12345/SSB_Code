//#define CO_FCY 70000
//#include "CANopen.h"
//#include "sensor_state.h"
//#include "sensor_can.h"
////#include "CO_driver.h"
//
//const CO_CANbitRateData_t  CO_CANbitRateData[8] = {CO_CANbitRateDataInitializers};
//
//can_data can_state;
//CO_t* co;
//
//return_value_t can_init()
//{
//    can_state.init_return = RET_OK;
//    co = 0;
//    int err;
//    err = CO_init(&co);
//    if(err){
//        can_state.init_return = RET_ERROR;
//    } else {
//        CO_CANsetNormalMode(ADDR_CAN1);
//    }
//    return can_state.init_return;
//}
//
//unsigned can_tick()
//{
//    return CO_process(co,1);
//}

#include "sensor_state.h"
#include "sensor_can.h"
#include "../libs/CanFestival-3/include/dspic33e/can_dspic33e.h"
#include "../libs/CanFestival-3/include/dspic33e/canfestival.h"
#include "ObjDict.h"

can_data can_state;
extern CO_Data ObjDict_Data;

return_value_t can_init()
{
    can_state.init_return = RET_OK;
    if(!canInit(1000000))
    {
        //fail
        can_state.init_return = RET_ERROR;
        return can_state.init_return;
    }
    //initialize CAN timer
    setNodeId (&ObjDict_Data, 0);
    setState(&ObjDict_Data, Initialisation);	// Init the state

    return can_state.init_return;
}

void can_process()
{
    Message* m;
    Message m_copy;
    if(canReceive(m)){
        m_copy = *m; //the packet could be overwritten in an interrupt, so copy it
        canDispatch(&ObjDict_Data, &m_copy); //send packet to CanFestival
    }
}