/* 
 * File:   motor_hallsensors.h
 * Author: ken
 *
 * Created on September 6, 2013, 11:42 PM
 */

#ifndef MOTOR_HALLSENSORS_H
#define	MOTOR_HALLSENSORS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "sensor_state.h"
    return_value_t hallsensors_init();

    void hallsensors_interpolate();
    




#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_HALLSENSORS_H */

