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
#include "sensor_hallsensors.h"
#include "sensor_pmsm.h"
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
    loadcell_init();
    LED_3 = 1;
    /*
    imu_init();
    rf_init();
    adc_init();
    */

    timers_init();
    hallsensors_init();
    pmsm_init();
    LED_4 = 1;
    state_init();
    led_rgb_set(0,100,255);
    LED_1 = 0;
    LED_2 = 1;
    LED_3 = 0;
    LED_4 = 0;
    pmsm_enable(1);
    pmsm_set_duty_cycle(0000,2000,4096);
    for(;;){
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;
            {
                //everything in here will be executed once every ms
                //make sure that everything in here takes less than 1ms
                //useful for checking state consistency, synchronization, watchdog...
                led_update();
                //LED_2= (timer_state.systime&0b100000000)!=0;
                //LED_3= (timer_state.systime&0b1000000000)!=0;
                //LED_4= (timer_state.systime&0b10000000000)!=0;
                //LED_1= (timer_state.systime&0b100000000000)!=0;
                led_colors+=1;
                led_rgb_set(((led_colors>>8)&0b1)<<5,((led_colors>>9)&0b1)<<5,((led_colors>>10)&0b1)<<5);
                //led_rgb_set((led_colors>>16)&0xFF,(led_colors>>8)&0xFF,led_colors&0xFF);
                //pmsm_update();
                LED_2 = !FAULT;
                LED_3 = !OCTW;
            }            
        } else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop
        }
    }
    return (EXIT_SUCCESS);
}

