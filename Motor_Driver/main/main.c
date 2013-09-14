/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 28, 2013, 11:31 PM
 */
#include "p33Exxxx.h"
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF & PWMLOCK_OFF);
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
#include "superball_communication.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern system_data system_state;
extern timer_data timer_state;
extern qei_data qei_state;
extern uart_data uart_state;
extern uart_data uart_sg_state;
extern hallsensor_data hallsensor_state;
extern motor_data motor_state;
extern loadcell_data loadcell_state;
extern hallsensor_data hallsensor_state;

/*
 * 
 */
int main(int argc, char** argv) {
    unsigned state_transmit_ctr = 0;
    unsigned udiff;
    superball_packet packet;
    uint8_t uart_rx_test[UART_RX_PACKET_MAX_LEN];
    uint8_t tmp[50];
    
    
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
    
    can_init();
    
    //loadcell_init();
    /*
    imu_init();
    rf_init();
    adc_init();
    */
    timers_init();
    superball_communication_init();
    state_init();

    pmsm_enable(1); //enable/disable gate drivers

    led_intensity_set(0,255,0,255);
    //pmsm_set_duty_cycle(1000,2000,3000);

    //can_transmit_packet(0);
    while(1){}
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
                led_intensity_set(60*(hallsensor_state.direction),((timer_state.systime&0x100)>0)*255,255*(!OCTW),255*(!FAULT));
                //led_update();
                qei_update();
                udiff = hallsensor_state.last_update_tmr;
                /*if(TMR1<hallsensor_state.last_update_tmr){
                    udiff = (TMR1+8750)-hallsensor_state.last_update_tmr;
                } else {
                    udiff = TMR1-hallsensor_state.last_update_tmr;
                }*/
                hallsensors_interpolate();
                pmsm_update();
                if(++state_transmit_ctr>50){
                    
                    state_transmit_ctr = 0;
                    /*uart_tx_packet = uart_tx_cur_packet();
                    uart_tx_packet[0] = 0xFF;//ALWAYS 0xFF
                    uart_tx_packet[1] = 0xFF;//CMD
                    uart_tx_packet[2] = 14+16;
                    uint32_t ms = (uint32_t)(motor_state.rotor_state);
                    uint32_t speed = (uint32_t)(motor_state.rotor_speed);
                    uart_tx_packet[3] = (speed>>8)&0xFF;
                    uart_tx_packet[4] = speed&0xFF;
                    uart_tx_packet[5] = (ms>>8)&0xFF;
                    uart_tx_packet[6] = ms&0xFF;
                    uart_tx_packet[7] = PDC1>>8;
                    uart_tx_packet[8] = PDC1&0xFF;
                    uart_tx_packet[9] = PDC2>>8;
                    uart_tx_packet[10] = PDC2&0xFF;
                    uart_tx_packet[11] = PDC3>>8;
                    uart_tx_packet[12] = PDC3&0xFF;
                    
                    for(i=0;i<4;++i){
                        uart_tx_packet[14+i*4] = (loadcell_state.values[i]>>24)&0xFF;
                        uart_tx_packet[14+i*4+1] = (loadcell_state.values[i]>>16)&0xFF;
                        uart_tx_packet[14+i*4+2] = (loadcell_state.values[i]>>8)&0xFF;
                        uart_tx_packet[14+i*4+3] = (loadcell_state.values[i])&0xFF;
                    }
                     
                    uart_tx_compute_cks(uart_tx_packet);
                    uart_tx_update_index();
                    uart_tx_start_transmit();*/

                    
                    superball_packet_init(&packet);
                    packet.data = malloc(sizeof(uint8_t)*20);
                    uint32_t ms = (uint32_t)(motor_state.rotor_state);
                    uint32_t speed = (uint32_t)(motor_state.rotor_speed);
                    packet.data[0] = (speed>>8)&0xFF;
                    packet.data[1] = speed&0xFF;
                    packet.data[2] = (ms>>8)&0xFF;
                    packet.data[3] = ms&0xFF;
                    for(i=0;i<4;++i){
                        packet.data[4+i*4] = (loadcell_state.values[i]>>24)&0xFF;
                        packet.data[4+i*4+1] = (loadcell_state.values[i]>>16)&0xFF;
                        packet.data[4+i*4+2] = (loadcell_state.values[i]>>8)&0xFF;
                        packet.data[4+i*4+3] = (loadcell_state.values[i])&0xFF;
                    }
                    //for(i=0;i<10;++i)
                    //    packet.data[i] = i+1;

                    //packet.data[0] = (uart_state.rx_num_errors>>24)&0xff;
                    //packet.data[1] = (uart_state.rx_num_errors>>16)&0xff;
                    //packet.data[2] = (uart_state.rx_num_errors>>8)&0xff;
                    //packet.data[3] = uart_state.rx_num_errors&0xFF;
                    //packet.data[6] = timer_state.systime&0xFF;
                    packet.header.length = 20;
                    //packet.header.origin = 1022;
                    //packet.interface_in = IF_LOCAL;
                    packet.header.destination = 0;
                    superball_route_packet(&packet);
                }
            }            
        } else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop

            //CHECK FOR RECEIVED WIFI MESSAGES
            uart_rx_packet=uart_rx_cur_packet();
            if(uart_rx_packet!=0){
                 if(uart_rx_packet[0]==0x55){
                    //SUPERBall packet
                    superball_packet_init(&packet);
                    for(i=0;i<uart_rx_packet[1]-2;++i){
                        uart_rx_test[i] = uart_rx_packet[2+i];
                    }
                    //memcpy(uart_rx_test,uart_rx_packet+2,UART_RX_PACKET_MAX_LEN-2);
                    if(superball_packet_deserialize(uart_rx_test,&packet)==SUCCESS){
                        packet.interface_in = IF_UDP;
                        superball_route_packet(&packet);
                    } else {
                    }
                } else{
                    //legacy messages???
                }
                /*
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
                }*/
                uart_rx_packet_consumed();

                system_state.ticks_since_last_cmd = 0;
            }
            //CHECK FOR RECEIVED CAN MESSAGES

            //CHECK FOR RECEIVED LOCAL MESSAGES

            //TRANSMIT CAN MESSAGES

            //TRANSMIT UART2 MESSAGES (STRAIN GAUGES)

            //TRANSMIT UDP MESSAGES (UART1)
            while(superball_next_transmit_packet(IF_UDP,&packet)){
                uart_tx_packet = uart_tx_cur_packet();
                //for(i=0;i<20;++i)
                //    uart_tx_packet[i] = 0;
                uart_tx_packet[0] = 0xFF;//ALWAYS 0xFF
                uart_tx_packet[1] = 0x55;//CMD
                uart_tx_packet[2] = superball_packet_length(&packet)+2;
                superball_packet_serialize(&packet,tmp);
                for(i=0; i<superball_packet_length(&packet);++i){
                    uart_tx_packet[3+i] = tmp[i];
                }
                uart_tx_packet[uart_tx_packet[2]+1] = 0;
                for(i=1;i<=uart_tx_packet[2];++i)
                    uart_tx_packet[uart_tx_packet[2]+1]^=uart_tx_packet[i];
                //uart_tx_compute_cks(uart_tx_packet);
                //uart_tx_packet[2]--;
                uart_tx_update_index();
                uart_tx_start_transmit();
                superball_free_packet(&packet);

            }

            
            
            

        }
    }
    return (EXIT_SUCCESS);
}
