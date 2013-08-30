/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 28, 2013, 11:31 PM
 */

#include "sensor_clock.h" //always include first, as this sets a number of config variables
#include <stdio.h>
#include <stdlib.h>
#include "sensor_adc.h"
#include "sensor_can.h"
#include "sensor_imu.h"
#include "sensor_led.h"
#include "sensor_loadcell.h"
#include "sensor_pindefs.h"
#include "sensor_rf.h"
#include "sensor_state.h"
#include "sensor_timers.h"

extern system_data system_state;
extern timer_data timer_state;

/*
 * 
 */
int main(int argc, char** argv) {
    clock_init();
    pin_init();
    led_init();
    /*
    can_init();
    loadcell_init();
    imu_init();
    rf_init();
    adc_init();
    */
    timers_init();
    state_init();
    
    for(;;){
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;
            {
                //everything in here will be executed once every ms
                //make sure that everything in here takes less than 1ms
                //useful for checking state consistency, synchronization, watchdog...
                led_update();
            }            
        } else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop
        }
    }
    return (EXIT_SUCCESS);
}

