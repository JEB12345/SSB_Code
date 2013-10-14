/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 28, 2013, 11:31 PM
 */

#include "sensor_clock.h" //always include first, as this sets a number of config variables
#include "sensor_adc.h"
#include "../libs/canopen/CANopen_stack/CANopen.h"
//#include "CO_PDO.h"
#include "sensor_can.h"
#include "sensor_imu.h"
#include "sensor_led.h"
#include "sensor_loadcell.h"
#include "sensor_pindefs.h"
#include "sensor_rf.h"
#include "sensor_state.h"
//#include "sensor_hallsensors.h"
//#include "sensor_pmsm.h"
#include "sensor_uart.h"
#include "sensor_timers.h"
#include <stdio.h>
#include <stdlib.h>
#include <p33Exxxx.h>

extern system_data system_state;
extern timer_data timer_state;
extern volatile rf_data rf_state;

void at_cmd_test_transmitted_tp_cb()
{
    
}

bool at_cmd_test_response_tp_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic)
{
    uint8_t* at_resp_param;
    int8_t temperature;
    //led_rgb_set(255,255,0);

    at_resp_param = xbee_at_cmd_data(raw_packet);

    temperature = at_resp_param[0];

    if(dynamic){
        free(raw_packet);
    }
    return 1;
}


void at_cmd_test_transmitted_cb()
{
    //led_rgb_set(0,255,0);
}

bool at_cmd_test_response_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic)
{
    //led_rgb_set(0,255,255);
    LED_4 = 1;
    if(status==1){
        led_rgb_set(0,0,255);
    } else {
        led_rgb_set(0,255,0);
        
    }
    xbee_at_cmd("TP",0,0,0,&rf_state.at_packet,at_cmd_test_transmitted_tp_cb,at_cmd_test_response_tp_cb,10);
    xbee_send_at_cmd();
    if(dynamic){
        free(raw_packet);
    }



    return 1;
}

/*
 * 
 */
int main(int argc, char** argv) {
    uint32_t led_colors = 0;
    uint8_t at_parm_test[10];
    unsigned once;
    volatile uint8_t* uart_tx_packet;
    LED_1 = 1;
    LED_2 = 0;
    LED_3 = 0;
    LED_4 = 0;
    clock_init();
    pin_init();
    led_init();
    LED_2 = 1;
    
    //can_init();
     
    
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
    uart_init();
    led_rgb_off();
    LED_1 = 0;
    LED_2 = 0;
    LED_3 = 0;
    LED_4 = 0;
    loadcell_init();
    loadcell_start();
     LED_1 = 0;
    LED_2 = 0;
    LED_3 = 0;
    LED_4 = 0;
    led_rgb_off();
    //pmsm_enable(1);
    //pmsm_set_duty_cycle(2000,2000,2000);
    //int i = 0;
    once = 0;
    rf_state.init_return = RET_UNKNOWN;
    for(;;){
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;
            {
                //everything in here will be executed once every ms
                //make sure that everything in here takes less than 1ms
                //useful for checking state consistency, synchronization, watchdog...
                rf_tick(1);
                //if(can_tick()){
                    //reset device
                //}

                led_update();
                //led_colors+=1;
                //led_rgb_set(0,255,0);
                //led_rgb_set((led_colors>>16)&0xFF,(led_colors>>8)&0xFF,led_colors&0xFF);
                //if(timer_state.systime&0b10000)
                    //loadcell_start();
                ClrWdt();
                if(timer_state.systime==100 && !once){
                    LED_1 = 0;
                    LED_2 = 0;
                    LED_3 = 0;
                    LED_4 = 0;
                    rf_init();
                    once = 1;
                    //LED_1 = 1;
                    //while(1);
                }
                if(timer_state.systime==500 && rf_state.init_return==RET_OK){
                    //send a test AT command
                    at_parm_test[0] = 0x1;
                    rf_state.at_packet.raw_packet.response_time_out = 0; //no callback
                    
                    //xbee_at_cmd_no_cb("AP",at_parm_test,1,0,&rf_state.at_packet);

                    xbee_at_cmd("AP",at_parm_test,1,0,&rf_state.at_packet,at_cmd_test_transmitted_cb,at_cmd_test_response_cb,10);

                    xbee_send_at_cmd();


                }
                if(timer_state.systime&0b100000){
                    LED_3=!LED_3;
                }
                if(timer_state.systime&0b10000 && 0){
                            uart_tx_packet = uart_tx_cur_packet();
                            //0:0XFF
                            //1:LEN
                            //2:(UPDATE BRAKE COAST DIR MODE)1
                            //3:PWMH1
                            //4:PWML1
                            //5:TORQUEH1
                            //6:TORQUEL1
                            //7:(UPDATE BRAKE COAST DIR MODE)2
                            //8:PWMH2
                            //9:PWML2
                            //10:TORQUEH2
                            //11:TORQUEL2
                            //12:(LED)
                            //13:(RESET)
                            //14:CS
                            uart_tx_packet[0] = 0xFF;//ALWAYS 0xFF
                            uart_tx_packet[1] = 0xFF;//CMD
                            uart_tx_packet[2] = 14;
                            uart_tx_packet[3] = 0b11110;
                            uart_tx_packet[4] = 0x0;//PWM
                            uart_tx_packet[5] = 0xFF;
                            uart_tx_packet[6] = 0xFF;//TORQUE
                            uart_tx_packet[7] = 0xFF;
                            uart_tx_packet[8] = 0b00000;
                            uart_tx_packet[9] = 0x0;//PWM
                            uart_tx_packet[10] = 0x0;
                            uart_tx_packet[11] = 0x0; //TORQUE
                            uart_tx_packet[12] = 0x0;
                            uart_tx_packet[13] = (timer_state.systime&0b100000)>0; //LED
                            uart_tx_packet[14] = 1; //RESET
                            uart_tx_compute_cks(uart_tx_packet);
                            uart_tx_update_index();
                            uart_tx_start_transmit();
                            
                        }
            }            
        } else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop
            if(rf_state.init_return==RET_OK){
                rf_process();
            }
        }
    }
    return (EXIT_SUCCESS);
}

