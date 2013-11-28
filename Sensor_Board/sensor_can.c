
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
extern motor_cmd_data motor_cmd_state[2];
extern loadcell_data loadcell_state;
static Message rec_m;
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

    setNodeId(&ObjDict_Data, 0x01);
    can_state.is_master = 1;
    can_enable_heartbeat(100);
//    if(P6_RA12){
//        setNodeId(&ObjDict_Data, 0x01);
//        can_state.is_master = 1;
//        can_enable_heartbeat(100);
//    }
//    else{
//        setNodeId(&ObjDict_Data, 0x02);
//        can_state.is_master = 0;
//    }
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
    while(canReceive(&rec_m)){
        //LED_1 ^= LED_1;
        //LED_3 = !LED_3;
        P6_RA11 = !P6_RA11;
        //memcpy(&m_copy,m,sizeof(Message));
        
        canDispatch(&ObjDict_Data, &rec_m); //send packet to CanFestival
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
//    d->post_SlaveStateChange = _can_post_SlaveStateChange;
//    can_start_node(nodeId);
//    can_enable_slave_heartbeat(nodeId, 33);
    
}

static void CheckSDOAndContinue(CO_Data* d, UNS8 nodeId)
{
        UNS32 abortCode;
        if(getWriteResultNetworkDict (d, nodeId, &abortCode) != SDO_FINISHED)

        /* Finalise last SDO transfer with this node */
        closeSDOtransfer(&ObjDict_Data, nodeId, SDO_CLIENT);

        ConfigureSlaveNode(d, nodeId);
}

static UNS32 motor_test_cb(CO_Data* d, const indextable * tbl, UNS8 bSubindex)
{
    //copy data to local motor state
    UNS32 s;
    void* res;
    uint8_t r8;
    uint16_t r16;
    uint32_t r32;
    UNS8 dtype;

    switch(bSubindex){
        case 0:
        case 1:
        case 2:
        case 3:
        case 10:
        case 11:
            s = sizeof(UNS8);
            res = &r8;
            break;
        case 6:
            s = sizeof(UNS32);
            res = &r32;
            break;
        case 4:
        case 5:
        case 7:
        case 8:
        case 9:
            s = sizeof(UNS16);
            res = &r16;
            break;
        default:
            return 0;
    };
    readLocalDict(d,0x2000,bSubindex,res,&s,&dtype,0);
    switch(bSubindex){
        case 0:
            break;
        case 1:
            motor_cmd_state[0].mode = r8;
            break;
        case 2:
            motor_cmd_state[0].brake = r8;
            break;
        case 3:
            motor_cmd_state[0].coast = r8;
            break;
        case 6:
            motor_cmd_state[0].position = r32;
            break;
        case 4:
            motor_cmd_state[0].vel = r16;
            break;
        case 5:
            motor_cmd_state[0].torque = r16;
            if(r16==0){
                while(1);
            }
            break;
        case 7:
            motor_cmd_state[0].p = r16;
            break;
        case 8:
            motor_cmd_state[0].i = r16;
            break;
        case 9:
            motor_cmd_state[0].d = r16;
            break;
        case 10:
                motor_cmd_state[0].dir = r8&0b1;
            break;
        case 11:
            motor_cmd_state[0].decay_mode = r8&0b1;
            break;
        default:
            return 0;
    };

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

    UNS32 pos[1] =  {123456789};
    UNS32 s = sizeof(UNS32);
    unsigned i;
    for(i=1;i<12;++i){
        RegisterSetODentryCallBack(&ObjDict_Data, 0x2000, i, motor_test_cb);
    }
//    writeLocalDict(&ObjDict_Data,   // CO_Data* for this uC
//            0x2000,                 // Index
//            0x06,                   // Sub-Index
//            pos,                   // void * SourceData Location
//            &s,                      // UNS8 * Size of Data
//            0);                    // UNS8 checkAccess
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

void can_push_state()
{
    UNS32 data_pos[1] = {(uint32_t)motor_cmd_state[0].cur_pos};
    UNS16 data_vel[1] = {(uint16_t)motor_cmd_state[0].cur_vel};
    UNS32 s = 0;
    UNS32 abortCode;
    UNS32 acode = 0;
    UNS8 wr =  getWriteResultNetworkDict (&ObjDict_Data, 3, &acode);
    static uint8_t state = 0;
//    if(wr!=SDO_FINISHED && wr != SDO_ABORTED_INTERNAL && wr!=0xA1 && wr!=0x80 ){
//        return;
//    }
    switch(state++){
        case 0:
            s = sizeof(UNS32);
            wr = writeNetworkDict(&ObjDict_Data,   // CO_Data* for this uC
            3,                 // Node Id
            0x2001  ,                 // Index
            0x01,                   // Sub-Index
            s,                      // UNS8 * Size of Data
            0,                      // Data type
            data_pos,                   // void * SourceData Location
            0);                    // UNS8 checkAccess
            if(wr){
                state--;
            }
            break;
        case 1:
            s = sizeof(UNS16);
            wr=writeNetworkDict(&ObjDict_Data,   // CO_Data* for this uC
            3,                 // Node Id
            0x2001  ,                 // Index
            0x02,                   // Sub-Index
            s,                      // UNS8 * Size of Data
            0,                      // Data type
            data_vel,                   // void * SourceData Location
            0);                    // UNS8 checkAccess
            if(wr){
                state--;
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            s = sizeof(UNS32);
            wr=writeNetworkDict(&ObjDict_Data,   // CO_Data* for this uC
            3,                 // Node Id
            0x2002  ,                 // Index
            state-2,                   // Sub-Index
            s,                      // UNS8 * Size of Data
            0,                      // Data type
            &loadcell_state.values[state-3],                   // void * SourceData Location
            0);                    // UNS8 checkAccess
            if(wr){
                state--;
            }
            break;
        default:
            state = 0;
            break;
    };

    
//    UNS32 acode = 0;
//    UNS8 wr =  getWriteResultNetworkDict (&ObjDict_Data, 3, &acode);

    s = sizeof(UNS16);
//
//    writeNetworkDict(&ObjDict_Data,   // CO_Data* for this uC
//            3,                 // Node Id
//            0x2001  ,                 // Index
//            0x02,                   // Sub-Index
//            s,                      // UNS8 * Size of Data
//            0,                      // Data type
//            data_vel,                   // void * SourceData Location
//            0);                    // UNS8 checkAccess
}