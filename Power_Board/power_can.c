
#include <p33Exxxx.h>
#include "power_state.h"

#include "../libs/dspic_CanFestival/CanFestival-3/include/dspic33e/can_dspic33e.h"

#include "power_can.h"
#include "power_pindef.h"
#include "power_objdict.h"

can_data can_state;
extern CO_Data Power_Board_Data;
static Message rec_m;

extern analog_data adc_values;

// Test Parameters for CANOpen
UNS32 PDO1_COBID = 0x0181;
UNS32 PDO2_COBID = 0x0281;
UNS32 sizeU32 = sizeof(UNS32);
UNS32 SINC_cicle=0;
UNS8 data_type = 0;

static void can_reset(CO_Data* d);
static void can_enable_heartbeat(uint16_t time);
static void can_enable_slave_heartbeat(UNS8 nodeId, uint16_t time);

return_value_t can_init()
{
    can_state.init_return = RET_OK;
    if(!canInit(1000))
    {
        //fail
        can_state.init_return = RET_ERROR;
        return can_state.init_return;
    }
    initTimer();
    
    //initialize CanFestival
    //reset callback
    Power_Board_Data.NMT_Slave_Node_Reset_Callback = can_reset;

    setNodeId(&Power_Board_Data, 0x03);
    can_state.is_master = 0;
    setState(&Power_Board_Data,Initialisation);

    PDOInit(&Power_Board_Data);

    return can_state.init_return;
}

uint8_t can_process()
{
    uint8_t res = 0;
    if(can_state.init_return!=RET_OK){
        return 0;
    } 
    while(canReceive(&rec_m)){     
        canDispatch(&Power_Board_Data, &rec_m); //send packet to CanFestival
        res = 1;
    }
    if(getState(&Power_Board_Data) != Operational){
        LED_G = 1;
        LED_B = 1;
    }

    switch(getState(&Power_Board_Data)){
        case Initialisation:
            LED_G = 1;
            LED_B = 1;
            break;
        case Pre_operational:
            LED_G = 0;
            LED_B = 1;
            break;
        case Operational:
            LED_G = 1;
            LED_B = 0;
            break;
        default:
            LED_G = 1;
            LED_B = 1;
            break;

    };

    return res;
}

void can_reset_node(uint8_t nodeId)
{
    masterSendNMTstateChange(&Power_Board_Data, nodeId, NMT_Reset_Node);
}

void can_start_node(uint8_t nodeId)
{
    masterSendNMTstateChange(&Power_Board_Data, nodeId, NMT_Start_Node);
}

static void _can_post_SlaveStateChange(CO_Data* d, UNS8 nodeId, e_nodeState newNodeState){
    if(nodeId==0x01){
        //TODO: You can handle state changes of other nodes here.
    }
}

static void ConfigureSlaveNode(CO_Data* d, UNS8 nodeId)
{
    setState(d, Operational);
//    d->post_SlaveStateChange = _can_post_SlaveStateChange;
//    can_start_node(nodeId);
//    can_enable_slave_heartbeat(nodeId, 33);
    
}

static void CheckSDOAndContinue(CO_Data* d, UNS8 nodeId)
{
        UNS32 abortCode;
        if(getWriteResultNetworkDict (d, nodeId, &abortCode) != SDO_FINISHED)

        /* Finalise last SDO transfer with this node */
        closeSDOtransfer(&Power_Board_Data, nodeId, SDO_CLIENT);

        ConfigureSlaveNode(d, nodeId);
}

void slaveInitTest()
{

}

void can_sync()
{
    sendSYNC(&Power_Board_Data);
}

static void can_reset(CO_Data* d)
{
    reset_board();
}

static UNS32 OnHeartbeatProducerUpdate(CO_Data* d, const indextable * unused_indextable, UNS8 unused_bSubindex)
{
  heartbeatStop(d);
  heartbeatInit(d);
  return 0;
}

static void can_enable_heartbeat(uint16_t time)
{
    UNS16 Timer_Data[1] = {time};
    UNS32 s = sizeof(UNS16);
    writeLocalDict(&Power_Board_Data,   // CO_Data* for this uC
            0x1017,                 // Index
            0x00,                   // Sub-Index
            Timer_Data,             // void * SourceData Location
            s,                      // UNS8 * Size of Data
            0);                     // UNS8 checkAccess
}

static void can_enable_slave_heartbeat(UNS8 nodeId, uint16_t time)
{
    /* Sample Code
    UNS32 data = 0x50;
    UNS8 size;
    UNS32 abortCode;
    writeNetworkDict(0, 0x05, 0x1016, 1, size, &data) // write the data index 1016 subindex 1 of node 5
    while (getWriteResultNetworkDict (0, 0x05, &abortCode) == SDO_DOWNLOAD_IN_PROGRESS);
    */
    UNS16 Timer_Data[1] = {time};
    UNS32 s = sizeof(UNS16);
    writeNetworkDict(&Power_Board_Data, // CO_Data* for this uC
            nodeId,                 // Node Id
            0x1017,                 // Index
            0x00,                   // Sub-Index
            s,                      // UNS8 * Size of Data
            0,                      // Data type
            Timer_Data,             // void * SourceData Location
            0);                     // UNS8 checkAccess
}

void can_time_dispatch()
{
    if(can_state.timer_flag){
        can_state.timer_flag = 0;
        TimeDispatch();
    }
}

void can_push_state()
{
    UNS32 data_1[1] = {adc_values.AN7};
    UNS32 s = 0;
    static uint8_t state = 0;

    switch(state++){
        case 0:
            s = sizeof(UNS32);
            writeLocalDict(&Power_Board_Data,   // CO_Data* for this uC
            0x3001,                // Index
            0x00,                  // Sub-Index]
            data_1,                // void * SourceData Location
            &s,                    // UNS8 * Size of Data
            1);                    // UNS8 checkAccess
            break;

//        case 1:
//        case 2:
//        case 3:

        default:
            state = 0;
            break;
    };
}