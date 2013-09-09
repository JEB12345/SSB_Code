/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 28, 2013, 11:31 PM
 */
#include "p33Exxxx.h"
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE);
_FWDT(FWDTEN_OFF);
/* Disable JTAG */
_FICD(JTAGEN_OFF & ICS_PGD2);
#include "motor_clock.h" //always include first, as this sets a number of config variables
#include "motor_adc.h"
#include "motor_can.h"
#include "motor_imu.h"
#include "motor_led.h"
#include "motor_loadcell.h"
#include "motor_uart.h"
#include "motor_qei.h"
#include "motor_pindefs.h"
#include "motor_rf.h"
#include "motor_state.h"
#include "motor_timers.h"
#include "motor_hallsensors.h"
#include "motor_pmsm.h"
#include <stdio.h>
#include <stdlib.h>

extern system_data system_state;
extern timer_data timer_state;
extern qei_data qei_state;
extern uart_data uart_state;
extern uart_data uart_sg_state;
extern hallsensor_data hallsensor_state;
extern motor_data motor_state;
extern loadcell_data loadcell_state;
/*
 * 
 */
int main(int argc, char** argv) {
    unsigned state_transmit_ctr = 0;
    volatile uint16_t* uart_tx_packet;
    volatile uint16_t* uart_rx_packet;
    unsigned i;
    clock_init();
    pin_init();
    led_init();
    qei_init();
    hallsensors_init();
    pmsm_init();
    uart_init();
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

    pmsm_enable(1); //enable/disable gate drivers

    led_intensity_set(0,255,0,255);

    pmsm_set_duty_cycle(0,0,0);

    for(;;){
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;
            {
                //everything in here will be executed once every ms
                //make sure that everything in here takes less than 1ms
                //useful for checking state consistency, synchronization, watchdog...
                //SAFETY: a simple watchdog timer to turn off the motor power if we didn't receive a command since some time
                system_state.ticks_since_last_cmd++;
                if(system_state.ticks_since_last_cmd>WATCHDOG_TIMEOUT){
                    //TODO: disable motor power
                }
                led_intensity_set(255*(hallsensor_state.cur_state==hallsensor_state.prev_state),0,0,0);
                led_update();
                qei_update();
                pmsm_update();
                if(++state_transmit_ctr>10){
                    state_transmit_ctr = 0;
                    uart_tx_packet = uart_tx_cur_packet();
                    uart_tx_packet[0] = 0xFF;//ALWAYS 0xFF
                    uart_tx_packet[1] = 0xFF;//CMD
                    uart_tx_packet[2] = 14+16;
                    uint32_t ms = (uint32_t)(motor_state.rotor_state*100);
                    uart_tx_packet[3] = (ms>>24)&0xFF;
                    uart_tx_packet[4] = (ms>>16)&0xFF;
                    uart_tx_packet[5] = (ms>>8)&0xFF;
                    uart_tx_packet[6] = ms&0xFF;
                    uart_tx_packet[7] = (uart_sg_state.packets_received>>24)&0xFF;
                    uart_tx_packet[8] = (uart_sg_state.packets_received>>16)&0xFF;
                    uart_tx_packet[9] = (uart_sg_state.packets_received>>8)&0xFF;
                    uart_tx_packet[10] = uart_sg_state.packets_received&0xFF;
                    uart_tx_packet[11] = hallsensor_state.cur_state;
                    uart_tx_packet[12] = (motor_state.rotor_turns>>8)&0xFF;
                    uart_tx_packet[13] = motor_state.rotor_turns&0xFF;
                    for(i=0;i<4;++i){
                        uart_tx_packet[14+i*4] = (loadcell_state.values[i]>>24)&0xFF;
                        uart_tx_packet[14+i*4+1] = (loadcell_state.values[i]>>16)&0xFF;
                        uart_tx_packet[14+i*4+2] = (loadcell_state.values[i]>>8)&0xFF;
                        uart_tx_packet[14+i*4+3] = (loadcell_state.values[i])&0xFF;
                    }
                    uart_tx_compute_cks(uart_tx_packet);
                    uart_tx_update_index();
                    uart_tx_start_transmit();
                }
            }            
        } else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop
            
            //Did we receive any commands?
            uart_rx_packet=uart_rx_cur_packet();
            if(uart_rx_packet!=0){

                if(uart_rx_packet[0]==0x01){
                    led_intensity_set(uart_rx_packet[2],uart_rx_packet[3],uart_rx_packet[4],uart_rx_packet[5]);
                } else if (uart_rx_packet[0]==0x0){
                    //PING
                    uart_tx_packet = uart_tx_cur_packet();
                    uart_tx_packet[0] = 0xFF;//ALWAYS 0xFF
                    uart_tx_packet[1] = 0xFF;//CMD
                    uart_tx_packet[2] = 4;
                    uart_tx_packet[3] = uart_rx_packet[2];
                    uart_tx_packet[4] = uart_rx_packet[3];
                    uart_tx_compute_cks(uart_tx_packet);
                    uart_tx_update_index();
                    uart_tx_start_transmit();
                }
                uart_rx_packet_consumed();

                system_state.ticks_since_last_cmd = 0;
            }


        }
    }
    return (EXIT_SUCCESS);
}

