/* 
 * File:   sensor_imu.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef SENSOR_IMU_H
#define	SENSOR_IMU_H
#include "sensor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif
#define IMU_ADDR    104
#define MAGNETOMETER_ADDR   0x0E
    return_value_t imu_init();

    //Read data from the IMU (non-blocking) and update the IMU state if possible
    void imu_read_state();


#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_IMU_H */

