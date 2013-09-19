/* 
 * File:   motor_pmsm.h
 * Author: ken
 *
 * Created on September 8, 2013, 4:48 PM
 */

#ifndef MOTOR_PMSM_H
#define	MOTOR_PMSM_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "sensor_state.h"
    /*
     * A thin wrapper around Pavlo's library
     */
    return_value_t pmsm_init();

    void pmsm_enable(unsigned enable);
    void pmsm_set_duty_cycle(uint16_t pwm1, uint16_t pwm2, uint16_t pwm3);
    void pmsm_update();




#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_PMSM_H */

