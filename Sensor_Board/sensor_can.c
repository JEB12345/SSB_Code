
#include "sensor_state.h"
#include "sensor_can.h"
#include "sensor_pindefs.h"
#include "ObjDict.h"

static Message* m;

can_data can_state;
extern CO_Data ObjDict_Data;
static Message* m;

return_value_t can_init()
{
    can_state.init_return = RET_OK;
    if(!canInit(1000))
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

uint8_t can_process()
{
    Message m_copy;
    if(canReceive(m)){
        m_copy = *m; //the packet could be overwritten in an interrupt, so copy it
        canDispatch(&ObjDict_Data, &m_copy); //send packet to CanFestival
        return 1;
    }
    else{
        return 0;
    }
}