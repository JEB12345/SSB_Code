/* 
 * File:   motor_control.h
 * Author: jonathan
 *
 * Created on September 27, 2014, 2:43 PM
 */

#ifndef MOTOR_CONTROL_H
#define	MOTOR_CONTROL_H

#include "sensor_can.h"
#include "sensor_loadcell.h"

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * This controller uses the basic impedance equation of
 * T = To + K(l-lo) + B(v-vo)
 * 
 * @param length
 * @param velocity
 * @return int32_t Tension
 */
int32_t impedance_controller(int16_t length, int16_t velocity);

/**
 * This is a basic controller for setting the given tension from the impedance controller
 * Proportional
 * @param desiredTension The tension setpoint in Newtons
 * @return int32_t setPosition
 */
int32_t force_controller(int32_t desiredTension);


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_CONTROL_H */

