/* 
 * File:   sensor_state.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:55 PM
 */

#ifndef SENSOR_STATE_H
#define	SENSOR_STATE_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum
        {
            RET_OK = 0,
            RET_ERROR = 1,
            RET_UNKNOWN = 127
        }
    return_value_t;

    //maintain all state variables here
    typedef struct {
        return_value_t          init_return;
        int volatile            state;
    } imu_data;
    
    typedef struct {
        return_value_t          init_return;
        volatile struct {
          uint16_t AN6;
          uint16_t AN7;
          uint16_t AN8;
          uint16_t AN11;
        } values;
    } adc_data;

    typedef struct {
        return_value_t          init_return;
        int volatile            state;
    } can_data;

    typedef struct {
        return_value_t          init_return;
        //sets the color of the RGB led
        uint8_t                 rgb_red;
        uint8_t                 rgb_green;
        uint8_t                 rgb_blue;
    } led_data;

    typedef struct {
        return_value_t          init_return;
        int volatile            state;
        uint32_t volatile       values[4];
    } loadcell_data;

    typedef struct {
        return_value_t          init_return;
        int volatile            state;
    } rf_data;

    typedef struct {
        return_value_t          init_return;
        unsigned int volatile   systime; //updated by a timer
        unsigned int            prev_systime;  //updated in main loop
    } timer_data;

    typedef enum {STATE_UNKNOWN = 0, STATE_INITIALIZED = 1, STATE_ERROR = 127} state_t;
    typedef struct {
        return_value_t          init_return;
        state_t volatile state; //system state
    } system_data;

    typedef struct {
        return_value_t          init_return;
        uint32_t                fcy;
    } clock_data;

    return_value_t state_init();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_STATE_H */

