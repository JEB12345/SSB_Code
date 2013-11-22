
#include <p33Exxxx.h>
#include "sensor_state.h"
//
//#include <dspic_CanFestival/CanFestival-3/include/lifegrd.h>
#include "dspic_CanFestival/CanFestival-3/include/dspic33e/can_dspic33e.h"

#include "sensor_can.h"
#include "sensor_pindefs.h"
#include "ObjDict.h"

can_data can_state;
extern CO_Data ObjDict_Data;
//static Message* m;

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
    ObjDict_Data.NMT_Slave_Node_Reset_Callback = can_reset;

    if(P6_RA12){
        setNodeId(&ObjDict_Data, 0x00);
        can_state.is_master = 1;
        can_enable_heartbeat(100);
    }
    else{
        setNodeId(&ObjDict_Data, 0x01);
        can_state.is_master = 0;
    }
    setState(&ObjDict_Data, Initialisation);	// Init the state
    //start heartbeat
    //can_enable_heartbeat(100);

    return can_state.init_return;
}

uint8_t can_process()
{
    //Message m_copy;
    uint8_t res = 0;
    if(can_state.init_return!=RET_OK){
        return 0;
    }
    Message m; ;
    while(canReceive(&m)){
        //LED_1 ^= LED_1;
        //LED_3 = !LED_3;
        P6_RA11 = !P6_RA11;
        //memcpy(&m_copy,m,sizeof(Message));
        
        canDispatch(&ObjDict_Data, &m); //send packet to CanFestival
        res = 1;
    }

    switch(getState(&ObjDict_Data)){
        case Initialisation:
            LED_2 = 0;
            LED_3 = 0;
            break;
        case Pre_operational:
            LED_2 = 1;
            LED_3 = 0;
            break;
        case Operational:
            LED_2 = 0;
            LED_3 = 1;
            break;
        default:
            LED_2 = 1;
            LED_3 = 1;
            break;

    };

    return res;
}

void can_reset_node(uint8_t nodeId)
{
    masterSendNMTstateChange(&ObjDict_Data, nodeId, NMT_Reset_Node);
}

void can_start_node(uint8_t nodeId)
{
    masterSendNMTstateChange(&ObjDict_Data, nodeId, NMT_Start_Node);
}

static void _can_post_SlaveStateChange(CO_Data* d, UNS8 nodeId, e_nodeState newNodeState){
    if(nodeId==0x01){
        //TODO: You can handle state changes of other nodes here.
    }
}

static void ConfigureSlaveNode(CO_Data* d, UNS8 nodeId)
{
    setState(d, Operational);
    d->post_SlaveStateChange = _can_post_SlaveStateChange;
    can_start_node(nodeId);
    can_enable_slave_heartbeat(nodeId, 33);
    
}

static void CheckSDOAndContinue(CO_Data* d, UNS8 nodeId)
{
        UNS32 abortCode;
        if(getWriteResultNetworkDict (d, nodeId, &abortCode) != SDO_FINISHED)

        /* Finalise last SDO transfer with this node */
        closeSDOtransfer(&ObjDict_Data, nodeId, SDO_CLIENT);

        ConfigureSlaveNode(d, nodeId);
}

void masterInitTest()
{
    UNS8 Timer_Data = 0x05;

    // Initalizes master RPDO1 to receive TPDO1 from ID=1
    writeLocalDict(&ObjDict_Data,   // CO_Data* for this uC
            0x1400,                 // Index
            0x01,                   // Sub-Index
            &PDO1_COBID,            // void * SourceData Location
            &sizeU32,                  // UNS8 * Size of Data
            RW);                    // UNS8 checkAccess

    // Setup Slave's TPDO1 to be transmitted on SYNC
//    writeNetworkDict(&ObjDict_Data,
//            0x01,   // ID
//            0x1017, // Heartbeat Timer Index
//            0x00,   // Subindex
//            1,      // Length
//            0,      // Data Type
//            &Timer_Data,    // Data
//            0);     // Don't Block

    ConfigureSlaveNode(&ObjDict_Data, 0x01);
}

void slaveInitTest()
{
    UNS8 Timer_Data = 0x05;
}

void can_sync()
{
    sendSYNC(&ObjDict_Data);
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
    writeLocalDict(&ObjDict_Data,   // CO_Data* for this uC
            0x1017,                 // Index
            0x00,                   // Sub-Index
            Timer_Data,             // void * SourceData Location
            &s,                     // UNS8 * Size of Data
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
    UNS32 abortCode;
    writeNetworkDict(&ObjDict_Data, // CO_Data* for this uC
            nodeId,                 // Node Id
            0x1017,                 // Index
            0x00,                   // Sub-Index
            s,                      // UNS8 * Size of Data
            0,                      // Data type
            Timer_Data,             // void * SourceData Location
            0);                     // UNS8 checkAccess
    //while(getWriteResultNetworkDict(&ObjDict_Data, nodeId, &abortCode) == SDO_DOWNLOAD_IN_PROGRESS);//cannot block the main loop!

}

void can_time_dispatch()
{
    if(can_state.timer_flag){
        can_state.timer_flag = 0;
        TimeDispatch();
    }
}