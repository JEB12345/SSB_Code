/* 
 * File:   sensor_rf.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:56 PM
 */

#ifndef SENSOR_RF_H
#define	SENSOR_RF_H
#include "sensor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif
#define XBEE_RESET_RETRIES  5 //how many times to try to reset the XBEE before failing
#define XBEE_RESET_WAIT_CYCLES  100000 //how many cycles to wait before the current XBEE reset trial has failed
    return_value_t rf_init();

    void rf_process();


#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_RF_H */

