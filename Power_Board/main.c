/* 
 * File:   main.c
 * Author: jonathan
 *
 * Created on March 20, 2014, 1:20 PM
 */

#include "clock.h"
#include "power_pindef.h"
#include "power_led.h"
#include "power_state.h"
#include "power_enable_pins.h"
#include "power_timers.h"
#include "power_adc.h"
#include <p33Exxxx.h>

extern timer_data timer_state;

/*
 * 
 */
int main(int argc, char** argv) {

    // Init Function Calls
    clock_init();
    pin_init();
    enable_pins_init();
    timers_init();
    init_adc();

    // Parameter Initalziations
    timer_state.prev_systime = 0;
    timer_state.systime = 0;
    uint16_t timeStep = 2000;


    //Diable Backup 5V5 and Enable MAIN 5V5
    EN_24V_5V5_IC = ON;
    EN_BACKUP_5V5 = OFF;
    EN_MAIN_5V5 = ON;

    BACKUP_CHARGE_EN = OFF;

    LED_STATUS = ON;

    //Enable 24V Line out to Motor
    MOTOR_EN = ON;
    G_BAT_KILL = OFF;
    G_BAT_PIC = OFF;

    for(;;){
        // All programs that run on a 1ms loop goes in this if statement
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;
            LED_STATUS = OFF;

            if(timer_state.systime%timeStep == 0){
               LED_1=!LED_1;
               MOTOR_EN = !MOTOR_EN;
            }

            if(timer_state.systime%50 == 0){
                LED_2 = !LED_2;
            }

        } else { //Everything else that needs to run faster than 1ms goes in the else statement
            
        }
    }

}

