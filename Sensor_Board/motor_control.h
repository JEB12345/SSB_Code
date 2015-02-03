/* 
 * File:   motor_control.h
 * Author: jonathan
 *
 * Created on September 27, 2014, 2:43 PM
 */

#ifndef MOTOR_CONTROL_H
#define	MOTOR_CONTROL_H

#include "sensor_can.h"

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * This controller uses the basic impedance equation of
 * T = To + K(l-lo) + B(v-vo)
 * 
 * @param length
 * @param velocity
 * @return uint32_t setTension
 */
INTEGER16 impedance_controller(INTEGER16 length, INTEGER16 velocity);


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_CONTROL_H */

