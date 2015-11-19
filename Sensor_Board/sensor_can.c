
#include <p33Exxxx.h>
#include "sensor_state.h"

#include "../libs/dspic_CanFestival/CanFestival-3/include/dspic33e/can_dspic33e.h"

#include "sensor_can.h"
#include "sensor_pindefs.h"
#ifdef CONF71
#include "sensor_objdict_71.h"
#else
#include "sensor_objdict_1.h"
#endif
#include "sensor_uart.h"
#include "sensor_loadcell.h"
#include "dwm1000_dspic/dwm_spi.h"
#include "MPU60xx/IMU.h"

can_data can_state;
extern CO_Data Sensor_Board_Data;
extern motor_cmd_data motor_cmd_state[2];
extern loadcell_data loadcell_state;
extern dwm_1000_status dwm_status;
static Message rec_m;

extern float mag_offset[9];
extern int16_t gyro_offset[3];
extern MPU6050_Data mpuData;

static void can_reset(CO_Data* d);
static void can_enable_heartbeat(uint16_t time);
static void can_enable_slave_heartbeat(UNS8 nodeId, uint16_t time);
static void ConfigureSlaveNode(CO_Data* d, unsigned char nodeId);

UNS32 mag_calibration_cb(CO_Data* d, const indextable * tbl, UNS8 bSubindex);

char heartbeat = 1;

return_value_t can_init()
{
    can_state.init_return = RET_OK;
    if(!canInit(1000))
    {
        //fail
        can_state.init_return = RET_ERROR;
        return can_state.init_return;
    }
//    LED_1;
    initTimer();
    
    //initialize CanFestival
    //reset callback
    Sensor_Board_Data.NMT_Slave_Node_Reset_Callback = can_reset;

#ifdef CONF71
    setNodeId(&Sensor_Board_Data, 0x71);
#else
    setNodeId(&Sensor_Board_Data, 0x01);
#endif
    can_state.is_master = 1;
    setState(&Sensor_Board_Data, Initialisation);	// Init the state
    setState(&Sensor_Board_Data, Operational);

#ifdef CONF71
    can_enable_slave_heartbeat(0x73,200);
    can_enable_slave_heartbeat(0x72,200);
    can_enable_heartbeat(200);
#else
    can_enable_slave_heartbeat(0x04,200);
    can_enable_slave_heartbeat(0x03,200);
    can_enable_slave_heartbeat(0x02,200);
    can_enable_heartbeat(200);
#endif

    PDOInit(&Sensor_Board_Data);

    RegisterSetODentryCallBack(&Sensor_Board_Data,0x2019,0x9,mag_calibration_cb);

    return can_state.init_return;
}

uint8_t can_process()
{
    uint8_t res = 0;
    if(can_state.init_return!=RET_OK){
        return 0;
    }

    while(canReceive(&rec_m)){
/***********This code will start any board which sends out a
	    pre-operational CANOpen code*/
//        if(rec_m.cob_id&0x0F){
//            if(rec_m.data[0] == 0x7F){
//                can_enable_slave_heartbeat((UNS16)rec_m.cob_id&0x0FF,100);
//                can_start_node(rec_m.cob_id&0x0FF);
//            }
//        }
        canDispatch(&Sensor_Board_Data, &rec_m); //send packet to CanFestival
        res = 1;
    }

//    switch(getState(&Sensor_Board_Data)){
//        case Initialisation:
//            LED_2 = 0;
//            LED_3 = 0;
//            break;
//        case Pre_operational:
//            LED_2 = 1;
//            LED_3 = 0;
//            break;
//        case Operational:
//            LED_2 = 0;
//            LED_3 = 1;
//            break;
//        default:
//            LED_2 = 1;
//            LED_3 = 1;
//            break;
//
//    };

    return res;
}

void can_reset_node(uint8_t nodeId)
{
    masterSendNMTstateChange(&Sensor_Board_Data, nodeId, NMT_Reset_Node);
}

void can_start_node(uint8_t nodeId)
{
    masterSendNMTstateChange(&Sensor_Board_Data, nodeId, NMT_Start_Node);
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
        closeSDOtransfer(&Sensor_Board_Data, nodeId, SDO_CLIENT);

        ConfigureSlaveNode(d, nodeId);
}

void masterInitTest()
{
   
}

void slaveInitTest()
{

}

void can_sync()
{
    sendSYNC(&Sensor_Board_Data);
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
    // checkAccess needs to be set to 1 
    UNS16 Timer_Data[1] = {time};
    UNS32 s = sizeof(UNS16);
    writeLocalDict(&Sensor_Board_Data,   // CO_Data* for this uC
            0x1017,                 // Index
            0x00,                   // Sub-Index
            Timer_Data,             // void * SourceData Location
            &s,                     // UNS8 * Size of Data
            1);                     // UNS8 checkAccess
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
    abortCode = writeNetworkDict(&Sensor_Board_Data, // CO_Data* for this uC
            nodeId,                 // Node Id
            0x1017,                 // Index
            0x00,                   // Sub-Index
            s,                      // UNS8 * Size of Data
            0,                      // Data type
            Timer_Data,             // void * SourceData Location
            0);                     // UNS8 useBlockData
}

void can_time_dispatch()
{
//    if(can_state.timer_flag){
//        can_state.timer_flag = 0;
//        TimeDispatch();
//    }
}

void can_push_state()
{
#ifdef CONF71
    if(abs(desired_motor_position_motor_72) > (MOTOR_POSITION_LIMIT * 1000.)){
        motor72_position_control_Commanded_Position = (MOTOR_POSITION_LIMIT * 1000.);
    }
    else{
        motor72_position_control_Commanded_Position = desired_motor_position_motor_72;
    }
#else
    if(abs(desired_motor_position_motor_2) > (MOTOR_POSITION_LIMIT * 1000.)){
        motor2_position_control_Commanded_Position = (MOTOR_POSITION_LIMIT * 1000.);
    }
    else{
        motor2_position_control_Commanded_Position = desired_motor_position_motor_2;
    }
#endif

	CO(strain_gauge_processed_Strain_Gauge_1P) = loadcell_bit_to_torque(loadcell_state.values[0],0);
//	CO(strain_gauge_processed_Strain_Gauge_2P) = loadcell_state.values[1];
//	CO(strain_gauge_processed_Strain_Gauge_3P) = loadcell_state.values[2];
//	CO(strain_gauge_processed_Strain_Gauge_4P) = loadcell_state.values[3];
//        CO(strain_gauge_processed_Strain_Gauge_5P) = loadcell_state.values[4];
//	CO(strain_gauge_processed_Strain_Gauge_6P) = loadcell_state.values[5];
//	CO(strain_gauge_processed_Strain_Gauge_7P) = loadcell_state.values[6];
//        CO(strain_gauge_processed_Strain_Gauge_8P) = loadcell_state.values[7];

	CO(strain_gauge_raw_Strain_Gauge_1R) = loadcell_state.values[0];
	CO(strain_gauge_raw_Strain_Gauge_2R) = loadcell_state.values[1];
	CO(strain_gauge_raw_Strain_Gauge_3R) = loadcell_state.values[2];
        CO(strain_gauge_raw_Strain_Gauge_4R) = loadcell_state.values[3];
	CO(strain_gauge_raw_Strain_Gauge_5R) = loadcell_state.values[4];
	CO(strain_gauge_raw_Strain_Gauge_6R) = loadcell_state.values[5];
        CO(strain_gauge_raw_Strain_Gauge_7R) = loadcell_state.values[6];
	CO(strain_gauge_raw_Strain_Gauge_8R) = loadcell_state.values[7];
    
    //DWM distance sensor
    CO(ranging_distances_node_1) = dwm_status.distance_mm[0];
    CO(ranging_distances_node_2) = dwm_status.distance_mm[1];
    CO(ranging_distances_node_3) = dwm_status.distance_mm[2];
    CO(ranging_distances_node_4) = dwm_status.distance_mm[3];
    CO(ranging_distances_node_5) = dwm_status.distance_mm[4];
    CO(ranging_distances_node_6) = dwm_status.distance_mm[5];
    CO(ranging_distances_node_7) = dwm_status.distance_mm[6];
    CO(ranging_distances_node_8) = dwm_status.distance_mm[7];
    CO(ranging_distances_node_9) = dwm_status.distance_mm[8];
    CO(ranging_distances_node_10) = dwm_status.distance_mm[9];
    CO(ranging_distances_node_11) = dwm_status.distance_mm[10];
    CO(ranging_distances_node_12) = dwm_status.distance_mm[11];
    CO(ranging_distances_node_13) = dwm_status.distance_mm[12];
    CO(ranging_distances_node_14) = dwm_status.distance_mm[13];
    CO(ranging_distances_node_15) = dwm_status.distance_mm[14];
    CO(ranging_distances_node_16) = dwm_status.distance_mm[15];
    // Added 4 more anchors
    CO(ranging_distances_node_18) = dwm_status.distance_mm[16];
    CO(ranging_distances_node_19) = dwm_status.distance_mm[17];
    CO(ranging_distances_node_20) = dwm_status.distance_mm[18];
    CO(ranging_distances_node_21) = dwm_status.distance_mm[19];
    //TODO: add support for distances transmitted by the fixed nodes

    if(dwm_status.new_data_flag){
        dwm_status.new_data_flag = 0; 
        sendOnePDOevent(&Sensor_Board_Data, 17); //0x1A11 should be the PDO for ranging data 1-4
        sendOnePDOevent(&Sensor_Board_Data, 18); //0x1A12 should be the PDO for ranging data 5-8
        sendOnePDOevent(&Sensor_Board_Data, 19); //0x1A13 should be the PDO for ranging data 9-12
        sendOnePDOevent(&Sensor_Board_Data, 20); //0x1A14 should be the PDO for ranging data 13-16
        // Added 4 more anchors
        sendOnePDOevent(&Sensor_Board_Data, 21); //0x1A15 should be the PDO for ranging data 18-21
    }
}

UNS32 mag_calibration_cb(CO_Data* d, const indextable * tbl, UNS8 bSubindex) {
    //set magnetometer parameters
    memcpy(mag_offset, CO(mag_cal_param), 9*sizeof(float));
    //reset gyro bias
    gyro_offset[0] = mpuData.gyroX;
    gyro_offset[1] = mpuData.gyroY;
    gyro_offset[2] = mpuData.gyroZ;
    return 0;
}