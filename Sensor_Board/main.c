/* 
 * File:   main.c
 * Author: ken and Jonathan
 *
 * Created on August 28, 2013, 11:31 PM
 * Latest Modification: 3 August, 2014
 */

#include "clock.h"
#include "sensor_can.h" //always include first, as this sets a number of config variables
#include "sensor_adc.h"
#include "sensor_imu.h"
#include "sensor_led.h"
#include "sensor_loadcell.h"
#include "sensor_pindefs.h"
#include "sensor_state.h"
#include "sensor_memdebug.h"
#include "sensor_uart.h"
#include "sensor_timers.h"
#include "sensor_memdebug.h"
#include "../libs/dspic_CanFestival/CanFestival-3/include/dspic33e/can_dspic33e.h"
#include <stdio.h>
#include <stdlib.h>
#include <p33Exxxx.h>


extern system_data system_state;
extern timer_data timer_state;
extern loadcell_data loadcell_state;
extern imu_data imu_state;
extern can_data can_state;


/*
 * 
 */
int main(int argc, char** argv) {
    uint32_t led_colors = 0;
    uint8_t at_parm_test[10];
    unsigned once;
    uint8_t i = 0;
    volatile uint8_t* uart_tx_packet = 0;
    volatile uint8_t* uart_rx_packet;
    uint32_t old_loadcell_data;
    uint16_t timeStep = 100;

    clock_init();
    pin_init();
    led_init();
    timers_init();
    state_init();
    uart_init();
    loadcell_init();
    loadcell_start();
    led_rgb_off();

    //memtest();

    imu_state.init_return = RET_UNKNOWN;
    //imu_init();

    led_rgb_set(50,0,100);

    // Commented out the CAN code since it has some while loops which hang if it is not connected.
    can_state.init_return = RET_UNKNOWN;
    if(can_init()){
        while(1);
    }

    timer_state.prev_systime = 0;
    timer_state.systime = 0;

    // Turn on the BBB by enabling the 5.5->5V LDO
//    BBB_Power = 1;

    // CANOpen test init for Master Node
//    if(can_state.is_master){
//        masterInitTest();
//    }
//    else{
//        slaveInitTest();
//    }

    for(;;){
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;
            //everything in here will be executed once every ms
            //make sure that everything in here takes less than 1ms
            //useful for checking state consistency, synchronization, watchdog...

            led_update();

            if(imu_state.init_return==RET_OK){
                imu_read_state();
            }
            if(can_state.init_return==RET_OK){
                can_process();

//                if(can_state.is_master){
//                    if(timer_state.systime==2000){
//                        //test reset slaves
//                        //can_reset_node(2);
//                    }
//                }
                if(timer_state.systime&timeStep){
//                    can_push_state();
                }
            }

            if(timer_state.systime%25 == 0){
               LED_4=!LED_4;
               LED_1=!LED_1;
            }

                if(timer_state.systime%1 == 0){
                    uart_tx_packet = uart_tx_cur_packet();
                    uart_tx_packet[0] = 0xFF;//counting
                    uart_tx_packet[1] = 0xFF;//CMD
                    uart_tx_packet[2] = 14;
                    //uart_tx_packet[3] = loadcell_state.sg_data_0;
                    uart_tx_packet[3] = (loadcell_state.values[0]>>16)&0xFF;
                    uart_tx_packet[4] = (loadcell_state.values[0]>>8)&0xFF;
                    uart_tx_packet[5] = (loadcell_state.values[0])&0xFF;
                    uart_tx_packet[6] = 0x01;
                    //uart_tx_packet[6] = 0xFF;
                    uart_tx_packet[7] = 0x89;// same as " "
                    //uart_tx_packet[7] = 0xFF;
                    //uart_tx_packet[8] = (loadcell_state.values[1]>>16)&0xFF;
                    uart_tx_packet[8] = 0xFF;
                    //uart_tx_packet[9] = (loadcell_state.values[1]>>8)&0xFF;
                    uart_tx_packet[9] = 0xFF;
                    //uart_tx_packet[10] = loadcell_state.values[1]&0xFF;
                    uart_tx_packet[10] = 0xFF;
                    uart_tx_packet[11] = 0x02;
                    //uart_tx_packet[11] = 0xFF;
                    uart_tx_packet[12] = 0x8b;// same as "\n"
                    //uart_tx_packet[12] = 0xFF;

                    uart_tx_compute_cks(uart_tx_packet);
                    uart_tx_update_index();
                    uart_tx_start_transmit();
                }
        }

        else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop
            
            if(!T1CONbits.TON){
                RGB_RED = 0;
                RGB_GREEN = RGB_BLUE = 1;
                while(1);

            }

            if(can_state.init_return==RET_OK){
                can_time_dispatch();
            }

            uart_rx_packet = uart_rx_cur_packet();
            if (uart_rx_packet != 0) {
                uart_rx_packet_consumed();
            }

        }
    }
    return (EXIT_SUCCESS);
}

