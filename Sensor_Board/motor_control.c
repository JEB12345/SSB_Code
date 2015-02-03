/* 
 * File:   motor_control.c
 * Author: jonathan
 *
 * Created on September 27, 2014, 2:43 PM
 */

#include "motor_control.h"

INTEGER16 impedance_controller(INTEGER16 length, INTEGER16 velocity)
{
	/**
	 * This controller uses the basic impedance equation of
	 * T = To + K(l-lo) + B(v-vo)
         * @param length
         * @param velocity
         * @return uint32_t setTension
         */

	INTEGER16 To = 1;	// Tension Offset
	INTEGER16 K = 1;	// Length Gain Value
	INTEGER16 B = 1;	// Velocity Gain Value
	INTEGER16 lo = 0;	// Length Offset
	INTEGER16 vo = 0;	// Velocity Offset

	INTEGER16 T = 0;	// Calculated Tension

	T = To + K*(length - lo) + B*(velocity - vo);
}