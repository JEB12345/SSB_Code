/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 28, 2013, 11:31 PM
 */

#include "motor_clock.h" //always include first, as this sets a number of config variables
#include "motor_adc.h"
#include "motor_can.h"
#include "motor_imu.h"
#include "motor_led.h"
//#include "motor_loadcell.h"
#include "motor_pindefs.h"
#include "motor_rf.h"
#include "motor_state.h"
#include "motor_timers.h"
#include <stdio.h>
#include <stdlib.h>

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
     */
    //loadcell_init();
    /*
    imu_init();
    rf_init();
    adc_init();
    */
    timers_init();
    state_init();

    led_intensity_set(16,255>>2,255>>1,255);
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

