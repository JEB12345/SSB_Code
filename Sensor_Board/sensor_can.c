
#include <p33Exxxx.h>
#include "sensor_state.h"
#include "sensor_can.h"
#include "sensor_pindefs.h"
#include "ObjDict.h"

can_data can_state;
extern CO_Data ObjDict_Data;
static Message* m;

// Test Parameters for CANOpen
UNS32 PDO1_COBID = 0x0181;
UNS32 PDO2_COBID = 0x0281;
UNS32 sizeU32 = sizeof(UNS32);
UNS32 SINC_cicle=0;
UNS8 data_type = 0;


return_value_t can_init()
{
    can_state.init_return = RET_OK;
    if(!canInit(1000))
    {
        //fail
        can_state.init_return = RET_ERROR;
        return can_state.init_return;
    }
    //initialize CanFestival
    if(P6_RA12){
        setNodeId(&ObjDict_Data, 0x00);
        can_state.is_master = 1;
    }
    else{
        setNodeId(&ObjDict_Data, 0x01);
        can_state.is_master = 0;
    }
    setState(&ObjDict_Data, Initialisation);	// Init the state
    return can_state.init_return;
}

uint8_t can_process()
{
    Message m_copy;
    if(canReceive(m)){
        LED_1 ^= LED_1;
        m_copy = *m; //the packet could be overwritten in an interrupt, so copy it
        canDispatch(&ObjDict_Data, &m_copy); //send packet to CanFestival
        return 1;
    }
    else{
        return 0;
    }
}

static void ConfigureSlaveNode(CO_Data* d, UNS8 nodeId)
{
    setState(d, Operational);

    masterSendNMTstateChange(d, nodeId, NMT_Start_Node);
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

    writeLocalDict(&ObjDict_Data,   // CO_Data* for this uC
            0x1017,                 // Index
            0x00,                   // Sub-Index
            &Timer_Data,                   // void * SourceData Location
            sizeof(UNS8),                      // UNS8 * Size of Data
            RW);                    // UNS8 checkAccess
}

void can_sync()
{
    sendSYNC(&ObjDict_Data);
}