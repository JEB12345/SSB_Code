/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 28, 2013, 11:31 PM
 */

#include "sensor_clock.h" //always include first, as this sets a number of config variables
#include "sensor_adc.h"
#include "sensor_iptest.h"
//#include "sensor_can.h"
#include "../libs/CanFestival-3/include/dspic33e/can_dspic33e.h"
#include "sensor_imu.h"
#include "sensor_led.h"
#include "sensor_loadcell.h"
#include "sensor_pindefs.h"
#include "sensor_rf.h"
#include "xbee_API.h"
#include "sensor_state.h"
#include "sensor_http.h"
#include "sensor_memdebug.h"
//#include "sensor_hallsensors.h"
//#include "sensor_pmsm.h"
#include "sensor_uart.h"
#include "sensor_timers.h"
#include "sensor_memdebug.h"
#include <stdio.h>
#include <stdlib.h>
#include <p33Exxxx.h>


extern system_data system_state;
extern timer_data timer_state;
extern volatile rf_data rf_state;
extern http_data http_state;
extern motor_cmd_data motor_cmd_state[2];
extern imu_data imu_state;
extern can_data can_state;
bool port_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic);
bool join_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic);

bool ip_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic)
{
    if(status==0){
        //if you need to know the IP address
    }
    rf_state.xbee_at_req = 0;
    return 1;
}

bool port_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic)
{
    //rf_state.xbee_at_req = 0;
//    if(dynamic){
//        free(raw_packet);
//    }
    //xbee_at_cmd("MY",0,0,0,&rf_state.at_packet,0,ip_cb,100);
    xbee_at_cmd("VR",0,0,0,&rf_state.at_packet,0,ip_cb,100);
    xbee_send_at_cmd();
    //LED_3=1;
    return 1;
}

bool join_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic)
{
    uint8_t data[2];
    //led_rgb_set(0,255,255);
    //LED_4 = 1;
    if(status==1){
        led_rgb_set(255,0,0);
            xbee_at_cmd("AI",0,0,0,&rf_state.at_packet,0,join_cb,500);
            xbee_send_at_cmd();
    } else {
        if(raw_packet[length-2]==0){
            led_rgb_set(0,255,0);
            rf_state.cur_network_status = INIT_SUCCESS;
            //set port
            data[0] = 0x1F;
            data[1] = 0x90;
            xbee_at_cmd("C0",data,2,0,&rf_state.at_packet,0,port_cb,100);
            xbee_send_at_cmd();
            //LED_4 = 1;
        }  else {
            led_rgb_set(0,0,255);
            xbee_at_cmd("AI",0,0,0,&rf_state.at_packet,0,join_cb,500);
            xbee_send_at_cmd();
        }
    }

//     if(dynamic){
//        free(raw_packet);
//    }

    return 1;
}

/*
 * 
 */
int main(int argc, char** argv) {
    uint32_t led_colors = 0;
    uint8_t at_parm_test[10];
    unsigned once;
    unsigned i;
    volatile uint8_t* uart_tx_packet;
    volatile uint8_t* uart_rx_packet;
    LED_1 = 1;
    LED_2 = 0;
    LED_3 = 0;
    LED_4 = 0;
    clock_init();
    pin_init();
    init_memory();
    for(i=0;i<100;++i)
        P7_RB4 = !P7_RB4;
    led_init();
    LED_2 = 1;
    
    //can_init(1000000);
     
    
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
    http_state.init_return = RET_UNKNOWN;

    //memtest();

    rf_init();
    network_init();

    imu_init();

    led_rgb_set(100,0,255);

    timer_state.prev_systime = 0;
    timer_state.systime = 0;
    P7_RB4 = 0;
    for(;;){
        if(timer_state.systime != timer_state.prev_systime){
            timer_state.prev_systime = timer_state.systime;
            {
                //everything in here will be executed once every ms
                //make sure that everything in here takes less than 1ms
                //useful for checking state consistency, synchronization, watchdog...
                rf_tick(1);
                if(timer_state.systime&0b100){
                    memcheck();
                }
                if(imu_state.init_return==RET_OK){
                    imu_read_state();
                }
                //can_tick();
                //network();


                
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
//                if(timer_state.systime==100 && !once){
//                    LED_1 = 0;
//                    LED_2 = 0;
//                    LED_3 = 0;
//                    LED_4 = 0;
//
//                    once = 1;
//                    //LED_1 = 1;
//                    //while(1);
//                } else
                   
                  //network scan
                /*/if(timer_state.systime==100){
                    //network reset
                    xbee_at_cmd_no_cb("NR",at_parm_test,0,0,&rf_state.at_packet);
                    xbee_send_at_cmd();
                } else */
//                if (timer_state.systime==300){
//                    //scan
//                    xbee_at_cmd_no_cb("AS",at_parm_test,0,0,&rf_state.at_packet);
//                    xbee_send_at_cmd();
//                }
                if(timer_state.systime==100 && rf_state.cur_network_status != INIT_SUCCESS)
                {
                    char* at_id = "Ken";//
                    xbee_at_cmd("ID",at_id,strlen(at_id),0,&rf_state.at_packet,0,0,0);
                    xbee_send_at_cmd();
                }
                else if(timer_state.systime==120 && rf_state.cur_network_status != INIT_SUCCESS)
                {
                    at_parm_test[0] = 2;
                    xbee_at_cmd("EE",at_parm_test,1,0,&rf_state.at_packet,0,0,0);
                    xbee_send_at_cmd();
                }else if(timer_state.systime==140 && rf_state.cur_network_status != INIT_SUCCESS)
                {
                    char* at_pk = "tensegrity";
                    xbee_at_cmd("PK",at_pk,strlen(at_pk),0,&rf_state.at_packet,0,0,0);
                    xbee_send_at_cmd();
                }
                else if(timer_state.systime==200 && rf_state.cur_network_status != INIT_SUCCESS)
                {
                    xbee_at_cmd("AI",at_parm_test,0,0,&rf_state.at_packet,0,join_cb,10000);
                    xbee_send_at_cmd();
                }
                else if (rf_state.cur_network_status == INIT_SUCCESS){
                    if(http_state.init_return==RET_UNKNOWN){
                        http_init();
                    } else if(http_state.init_return==RET_OK){
                        http_process();
                    }
                    if(!once){
                        iptest_init();
                        once = 1;
                    }
                }

//                if(timer_state.systime==500 && rf_state.init_return==RET_OK){
//                    //send a test AT command
//                    at_parm_test[0] = 0x1;
//                    rf_state.at_packet.raw_packet.response_time_out = 0; //no callback
//
//                    //xbee_at_cmd_no_cb("AP",at_parm_test,1,0,&rf_state.at_packet);
//
//                    xbee_at_cmd("AP",at_parm_test,1,0,&rf_state.at_packet,at_cmd_test_transmitted_cb,at_cmd_test_response_cb,10);
//
//                    xbee_send_at_cmd();
//
//
//                }
                

//                if(timer_state.systime>800 && rf_state.init_return==RET_OK ){
//                    char AT_cmd[2];
//                    unsigned parmlen;
//                    switch(timer_state.systime){
//                        case 800:
//                            at_parm_test[0] = 0x1;
//                            parmlen=0;
//                            break;
//                        case 950:
//                            break;
//                        default:
//                            AT_cmd[0] = 0;
//                    };
//                    if(AT_cmd[0]!=0){
//                        xbee_at_cmd_no_cb(AT_cmd,at_parm_test,parmlen,0,&rf_state.at_packet);
//                        xbee_send_at_cmd();
//                    }
//                }

//                if(timer_state.systime==1000){
//                    //fake an rx message
//                    xbee_rx_ip_packet_t ip_rx;
//                    char* req = "GET /test HTTP/1.0\r\n"
//                        "Host: 0.0.0.0:5000\r\n"
//                        "User-Agent: ApacheBench/2.3\r\n"
//                        "Accept: */*\r\n";
//                    ip_rx.raw_packet.length = strlen(req)+15;
//                    ip_rx.raw_packet.raw_data = malloc(ip_rx.raw_packet.length);
//                    memcpy(ip_rx.raw_packet.raw_data+14,req,strlen(req));
//                    ip_rx.options.checksum_error = 0;
//                    ip_rx.options.frame_id = XBEE_API_FRAME_RX_IPV4;
//                    ip_rx.options.protocol = XBEE_NET_IPPROTO_TCP;
//                    ip_rx.options.source_port = 9876;
//                    ip_rx.options.dest_port = 80;
//                    ip_rx.options.source_addr[0] = 192;
//                    ip_rx.options.source_addr[1] = 168;
//                    ip_rx.options.source_addr[2] = 1;
//                    ip_rx.options.source_addr[3] = 12;
//                    ip_rx.options.total_packet_length = ip_rx.raw_packet.length-15;
//                    ip_rx.raw_packet.dynamic = 1;
//                    if(CB_WriteMany(&rf_state.ip_rx_buffer,&ip_rx,sizeof(xbee_rx_ip_packet_t),1)==SUCCESS){
//                        //success
//                    } else {
//                        //if we cannot add it to the circular buffer, free the memory
//                        free(ip_rx.raw_packet.raw_data);
//                    }
//                }

                if(timer_state.systime&0b100000){
                   LED_4=!LED_4;
                }
                if(timer_state.systime&0b100000000 && rf_state.cur_network_status == INIT_SUCCESS){

                   led_rgb_set(0,255,0);
                   }
                if(timer_state.systime&0b10000 ){
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
                            uart_tx_packet[3] = 0b10110 | (motor_cmd_state[0].brake<<3);
                            uart_tx_packet[4] = motor_cmd_state[0].vel>>8;//0xFF;//PWM
                            uart_tx_packet[5] = motor_cmd_state[0].vel&0xFF;//0xFF;
                            uart_tx_packet[6] = motor_cmd_state[0].torque>>8;//0xFF;//TORQUE
                            uart_tx_packet[7] = motor_cmd_state[0].torque&0xFF;
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
                            led_rgb_set(0,255,100);
                        }

            }            
        } else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop

//            if(can_state.init_return ==RET_OK){
//                if(can_process()){
//                    LED_1 = 1;
//                }
//                else{
//                    LED_1 = 0;
//                }
//            }
            //memcheck();
            if(rf_state.init_return==RET_OK){
                rf_process();
            }


            //memcheck();

            uart_rx_packet = uart_rx_cur_packet();
        if (uart_rx_packet != 0) {
            //led_toggle();
            if(uart_rx_packet[0]==0xFF){
                
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

            }
            uart_rx_packet_consumed();

        }

        }
    }
    return (EXIT_SUCCESS);
}

