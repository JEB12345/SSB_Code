/* 
 * File:   motor_qei.h
 * Author: ken
 *
 * Created on September 5, 2013, 11:57 PM
 */

#ifndef MOTOR_QEI_H
#define	MOTOR_QEI_H

#include "motor_state.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    return_value_t qei_init();
    //copies the current encoder state to the qei_state variable
    void qei_update();


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_QEI_H */

