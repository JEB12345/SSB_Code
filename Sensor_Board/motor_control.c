/* 
 * File:   motor_control.c
 * Author: jonathan
 *
 * Created on September 27, 2014, 2:43 PM
 */

#include "motor_control.h"

extern loadcell_data loadcell_state;

int32_t impedance_controller(int16_t length, int16_t velocity)
{
	/**
	 * This controller uses the basic impedance equation of
	 * T = To + K(l-lo) + B(v-vo)
         * @param length
         * @param velocity
         * @return int32_t T
         */

	INTEGER16 To = 1;	// Tension Offset
	INTEGER16 K = 1;	// Length Gain Value
	INTEGER16 B = 1;	// Velocity Gain Value
	INTEGER16 lo = 0;	// Length Offset
	INTEGER16 vo = 0;	// Velocity Offset

	INTEGER16 T = 0;	// Calculated Tension

	T = (int32_t)(To + K*(length - lo) + B*(velocity - vo));
	return T;
}

int32_t force_controller(int32_t desiredTension)
{
	/**
	 * This controller uses a basic P controller
         * @param desiredTension
         * @return int32_t setPosition
         */
	
	int16_t K = 1;
	
	int32_t sgTension;
	int32_t setVelocity;

	sgTension = (loadcell_bit_to_torque(loadcell_state.values[0], 0)) / 15; // Hard coded spool radius in mm

	setVelocity = K * (sgTension - desiredTension);

	return setVelocity;
}