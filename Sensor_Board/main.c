/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 28, 2013, 11:31 PM
 */

#include "sensor_clock.h" //always include first, as this sets a number of config variables
#include "sensor_adc.h"
#include "sensor_can.h"
#include "sensor_imu.h"
#include "sensor_led.h"
#include "sensor_loadcell.h"
#include "sensor_pindefs.h"
#include "sensor_rf.h"
#include "sensor_state.h"
//#include "sensor_hallsensors.h"
//#include "sensor_pmsm.h"
#include "sensor_timers.h"
#include <stdio.h>
#include <stdlib.h>
#include <p33Exxxx.h>

extern system_data system_state;
extern timer_data timer_state;

/*
 * 
 */
int main(int argc, char** argv) {
    uint32_t led_colors = 0;
    LED_1 = 1;
    LED_2 = 0;
    LED_3 = 0;
    LED_4 = 0;
    clock_init();
    pin_init();
    led_init();
    LED_2 = 1;
    /*
    can_init();
     */
    
    LED_3 = 1;
    /*
    imu_init();
    rf_init();
    adc_init();
    */

    timers_init();
    //hallsensors_init();
    //pmsm_init();
    LED_4 = 1;
    state_init();
    led_rgb_set(0,0,0);
    LED_1 = 0;
    LED_2 = 1;
    LED_3 = 0;
    LED_4 = 0;
    loadcell_init();
    loadcell_start();
    //pmsm_enable(1);
    //pmsm_set_duty_cycle(2000,2000,2000);
    //int i = 0;
    for(;;){
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;
            {
                //everything in here will be executed once every ms
                //make sure that everything in here takes less than 1ms
                //useful for checking state consistency, synchronization, watchdog...
                led_update();
                led_colors+=1;
                //led_rgb_set(0,255,0);
                //led_rgb_set((led_colors>>16)&0xFF,(led_colors>>8)&0xFF,led_colors&0xFF);
                //if(timer_state.systime&0b10000)
                    //loadcell_start();
            }            
        } else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop
        }
    }
    return (EXIT_SUCCESS);
}

