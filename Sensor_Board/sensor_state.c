#include "sensor_state.h"
#include <p33Exxxx.h>

    system_data system_state;
    motor_cmd_data motor_cmd_state[2];

return_value_t state_init()
{
    int i;
    system_state.init_return = RET_OK;
    system_state.state = STATE_INITIALIZED;
    for(i=0;i<2;++i){
        motor_cmd_state[i].brake = 1;
        motor_cmd_state[i].vel = 0;
        motor_cmd_state[i].torque = 0;
        motor_cmd_state[i].coast = 0;
        motor_cmd_state[i].mode = 0;
        motor_cmd_state[i].p = 0xFFFF;
        motor_cmd_state[i].i = 0x00;
        motor_cmd_state[i].d = 0x00;
        motor_cmd_state[i].position = 0;
        motor_cmd_state[i].dir = 0;
        motor_cmd_state[i].decay_mode = 0;
    }
    
    /*
    mag_calibration.magX.xx = 2.2665e-03;
    mag_calibration.magX.xy = -8.7954e-05;
    mag_calibration.magX.xz = 2.4090e-04;
    mag_calibration.magX.offset = -748.7532;
    
    mag_calibration.magY.yx = -8.7954e-05;
    mag_calibration.magY.yy = 2.2866e-03;
    mag_calibration.magY.yz = 9.1031e-05;
    mag_calibration.magY.offset = 1163.7578;
    
    mag_calibration.magZ.zx = 2.4090e-04;
    mag_calibration.magZ.zy = 9.1031e-05;
    mag_calibration.magZ.zz = 1.9000e-03;
    mag_calibration.magZ.offset = 2872.2238;
    
    
     * Data from normal day Nov. 4 2015
    mag_calibration.magX.xx = 2.2470e-03;
    mag_calibration.magX.xy = -6.1081e-05;
    mag_calibration.magX.xz = 4.7808e-05;
    mag_calibration.magX.offset = -711.9643;
    
    mag_calibration.magY.yx = -6.1081e-05;
    mag_calibration.magY.yy = 2.5594e-03;
    mag_calibration.magY.yz = 1.90215e-04;
    mag_calibration.magY.offset = 1189.6026;
    
    mag_calibration.magZ.zx = 4.7808e-05;
    mag_calibration.magZ.zy = 1.90215e-04;
    mag_calibration.magZ.zz = 1.9043e-03;
    mag_calibration.magZ.offset = 2888.6265;
     * */
    
    //original fit tol=0.1
    //        int16_t magX[4] = {224, -6, -4, -712};
//        int16_t magY[4] = {-6, 256, -19, 1190};
//        int16_t magZ[4] = {-4, -19, 190, -2889};
    return system_state.init_return;
}

void reset_board()
{
    asm ("RESET");
    while(1);
}