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
#include "power_uart.h"
#include "power_can.h"
#include "superball_communication.h"
#include <p33Exxxx.h>

extern timer_data timer_state;
extern analog_data adc_values;
extern can_data can_state;

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
    uart_init();
    
    // Parameter Initalziations
    timer_state.prev_systime = 0;
    timer_state.systime = 0;
    uint16_t timeStep = 2000;
    volatile uint8_t* uart_tx_packet = 0;
//    volatile uint8_t* uart_rx_packet = 0;

    EN_OUT_1 = 1;
    EN_OUT_2 = 1;
    EN_OUT_3 = 1;
    EN_OUT_4 = 1;

    //Enable Motor Output
    KILLSWITCH_uC = ON;

    LED_B = ON;

    // Enable CAN after calling the EN_OUT_# commands.
    // This prevents the while loop in the can_init() from stalling.
    can_state.init_return = RET_UNKNOWN;
//    if(can_init()){
//        while(1);
//    }

    for(;;){
        // All programs that run on a 1ms loop should go in this if statement
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;

            if(timer_state.systime%timeStep == 0){
               LED_B=!LED_B;
            }

            if(timer_state.systime%50 == 0){
                LED_G = !LED_G;
            }

            if(timer_state.systime%1 == 0){
                uart_tx_packet = uart_tx_cur_packet();
                uart_tx_packet[0] = 0xFF;//ALWAYS 0xFF
                uart_tx_packet[1] = 0xFF;//CMD
                uart_tx_packet[2] = 14;
                uart_tx_packet[3] = (adc_values.AN6>>8)&0xFF;
                uart_tx_packet[4] = adc_values.AN6&0xFF;
                uart_tx_packet[5] = (adc_values.AN7>>8)&0xFF;
                uart_tx_packet[6] = adc_values.AN7&0xFF;
                uart_tx_packet[7] = (adc_values.AN8>>8)&0xFF;
                uart_tx_packet[8] = adc_values.AN8&0xFF;
                uart_tx_packet[9] = (adc_values.AN11>>8)&0xFF;
                uart_tx_packet[10] = adc_values.AN11&0xFF;

                uart_tx_compute_cks(uart_tx_packet);
                uart_tx_update_index();
                uart_tx_start_transmit();

            }

            if(can_state.init_return==RET_OK){
                can_process();

                if(can_state.is_master){
                    if(timer_state.systime==2000){
                        //test reset slaves
                        //can_reset_node(2);
                    }
                }
                if(timer_state.systime&0b100000000){
//                     can_push_state();
                }
            }

        } else { //Everything else that needs to run faster than 1ms goes in the else statement

            /*******************************************************************
             * Software controlled switching between VBAT_5V5 and VBACKUP_5V5
             * 
             ******************************************************************/
            if((adc_values.AN7)>0x0960){
                VBAT_5V5_EN = ON;
                EN_BACKUP_5V5 = OFF;
                EN_VBAT_5V5 = ON;
                LED_STATUS = OFF;
            }
            else{
                EN_BACKUP_5V5 = ON;
                VBAT_5V5_EN = OFF;
                EN_VBAT_5V5 = OFF;
                LED_STATUS = ON;
            }

            /*******************************************************************
             * Software controlled Killswitch for power switch
             * 
             * why? -> Because the PMOS does not turn off VBAT_5V5 when the main
             * power switch is flipped off. This is not ideal and will not always
             * cut power to board when VBAT_5V5 is main power source.
             ******************************************************************/
            if(adc_values.AN8<0x0800){
                VBAT_5V5_EN = OFF;
            }

            if(can_state.init_return==RET_OK){
                can_time_dispatch();
            }
        }
    }

}
