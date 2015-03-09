/* 
 * File:   power_killswitch.c
 * Author: ken
 *
 * Created on March 3, 2015, 5:15 PM
 */

#include "power_state.h"

killswitch_data killswitch_state;
extern analog_data adc_values;

return_value_t killswitch_init()
{
    killswitch_state.power_bad_ctr = 0;
    killswitch_state.power_good_ctr = 0;
    killswitch_state.state = KS_OFF;
    return RET_OK;
}

/*
 * 
 */
void killswitch_update()
{
    bool pwr_good = adc_values.mV_main_battery > 22500;
    bool pwr_critical = adc_values.mV_main_battery < 21000;
    
    //state machine: update events
    if(pwr_good){
        killswitch_state.power_good_ctr++;
        killswitch_state.power_bad_ctr = 0;
    } else {
        killswitch_state.power_good_ctr = 0;
        killswitch_state.power_bad_ctr++;
    }

    //avoid overflow
    if(killswitch_state.power_bad_ctr>=1000){
        killswitch_state.power_bad_ctr = 1000;
    }
    if(killswitch_state.power_good_ctr>=1000){
        killswitch_state.power_good_ctr = 1000;
    }
    
    //state machine: update state
    killswitch_power_state old_state = killswitch_state.state;
    switch(killswitch_state.state){
        case KS_ON:
            if(pwr_critical){
                killswitch_state.state = KS_OFF;
            } else if(killswitch_state.power_bad_ctr>5){
                killswitch_state.state = KS_OFF;
            }
            break;
        case KS_OFF:
            if(killswitch_state.power_good_ctr>10){
                killswitch_state.state = KS_ON;
            }
            break;
    }

    if(old_state != killswitch_state.state){
        killswitch_state.power_bad_ctr = 0;
        killswitch_state.power_good_ctr = 0;
    }
}

