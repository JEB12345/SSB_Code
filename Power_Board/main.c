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
#include <p33Exxxx.h>

extern timer_data timer_state;
extern analog_data adc_values;

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

    //Diable Backup 5V5 and Enable MAIN 5V5
    EN_24V_5V5_IC = ON;
    EN_BACKUP_5V5 = OFF;
    EN_MAIN_5V5 = ON;

    /*
    BACKUP_CHARGE_EN = OFF; // Inverted Logic
    */

    LED_STATUS = ON;

    EN_OUT_1 = 1;
    EN_OUT_2 = 1;
    EN_OUT_3 = 1;
    EN_OUT_4 = 1;

    //Enable 24V Line out to Motor
//    MOTOR_EN = ON; //Make sure this is off once the kill switch is attached.
//    G_BAT_KILL = OFF;
//    G_BAT_PIC = OFF;

    LED_STATUS = OFF;

    for(;;){
        // All programs that run on a 1ms loop should go in this if statement
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;

            if(timer_state.systime%timeStep == 0){
               LED_1=!LED_1;
            }

            if(timer_state.systime%50 == 0){
                LED_2 = !LED_2;
            }

            if(timer_state.systime%100 == 0){
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

            if(timer_state.systime%5000 == 0){
                MOTOR_EN = ON;
            }

        } else { //Everything else that needs to run faster than 1ms goes in the else statement
            if(!(adc_values.AN11>>7)){
                //BACKUP_CHARGE_EN = ON; //Inverted Logic
                EN_BACKUP_5V5 = ON;
                EN_24V_5V5_IC = OFF;
                LED_STATUS = ON;
            }
            else{
                EN_BACKUP_5V5 = OFF;
                EN_24V_5V5_IC = ON;
                //BACKUP_CHARGE_EN = OFF; //Inverted Logic
                LED_STATUS = OFF;
            }
        }
    }

}

