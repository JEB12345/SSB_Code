/* 
 * File:   power_state.h
 * Author: jonathan
 *
 * Created on March 18, 2014, 7:53 AM
 */

#ifndef POWER_STATE_H
#define	POWER_STATE_H

#include <stdint.h>

// Defining ON and OFF
enum {
    OFF,
    ON
};

// Universal return values
typedef enum {
    RET_OK = 0,
    RET_ERROR = 1,
    RET_UNKNOWN = 127
} return_value_t;

// Used to init the clock
typedef struct {
    return_value_t          init_return;
    uint32_t                fcy;
} clock_data;

// Main 1ms loop timer data
typedef struct {
        return_value_t          init_return;
        unsigned int volatile   systime;        //updated by a timer
        unsigned int            prev_systime;   //updated in main loop
    } timer_data;

#endif	/* POWER_STATE_H */

