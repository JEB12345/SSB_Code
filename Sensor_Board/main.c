/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 28, 2013, 11:31 PM
 */

#include "clock.h"
#include "sensor_can.h" //always include first, as this sets a number of config variables
#include "sensor_adc.h"
#include "sensor_iptest.h"
#include "sensor_imu.h"
#include "sensor_led.h"
#include "sensor_loadcell.h"
#include "sensor_pindefs.h"
#include "sensor_rf.h"
#include "xbee_API.h"
#include "sensor_state.h"
#include "sensor_http.h"
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
extern volatile rf_data rf_state;
extern http_data http_state;
extern motor_cmd_data motor_cmd_state[2];
extern loadcell_data loadcell_state;
extern imu_data imu_state;
extern can_data can_state;
//bool port_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic);
//bool join_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic);
//
//bool ip_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic)
//{
//    uint8_t pkt[40];
//    uint16_t i;
//    if(status==0){
//        //if you need to know the IP address
//        for(i=0;i<length;++i){
//            pkt[i]=raw_packet[i];
//        }
//    }
//    //TODO: store the address, so it becomes accessible over CAN
//    rf_state.xbee_at_req = 0;
//    return 1;
//}
//
//bool port_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic)
//{
//    xbee_at_cmd("MY",0,0,0,&rf_state.at_packet,0,ip_cb,100);
//    xbee_send_at_cmd();
//    return 1;
//}
//
//bool join_cb(uint8_t frame_id, uint16_t at_cmd, uint8_t status, uint8_t* raw_packet, uint16_t length,bool dynamic)
//{
//    uint8_t data[2];
//    if(status==1){
//        led_rgb_set(255,0,0);
//            xbee_at_cmd("AI",0,0,0,&rf_state.at_packet,0,join_cb,500);
//            xbee_send_at_cmd();
//    } else {
//        if(raw_packet[length-2]==0){
//            led_rgb_set(0,255,0);
//            rf_state.cur_network_status = INIT_SUCCESS;
//
//            //set port
//            data[0] = 0x1F;
//            data[1] = 0x90;
//            xbee_at_cmd("C0",data,2,0,&rf_state.at_packet,0,port_cb,100);
//            xbee_send_at_cmd();
//        }  else {
//            led_rgb_set(0,0,255);
//            xbee_at_cmd("AI",0,0,0,&rf_state.at_packet,0,join_cb,500);
//            xbee_send_at_cmd();
//        }
//    }
//    return 1;
//}

/*
 * 
 */
int main(int argc, char** argv) {
    uint32_t led_colors = 0;
    uint8_t at_parm_test[10];
    unsigned once;
    uint8_t i = 0;
    volatile uint8_t* uart_tx_packet;
    volatile uint8_t* uart_rx_packet;
    uint32_t old_loadcell_data;

    clock_init();
    pin_init();
    SHD = 0;

    init_memory();
    
    led_init();

    timers_init();
    state_init();
    uart_init();
    loadcell_init();
    loadcell_start();
    led_rgb_off();

    once = 0;
    rf_state.init_return = RET_UNKNOWN;
    http_state.init_return = RET_UNKNOWN;

    //memtest();

    rf_init();
    network_init();

    imu_state.init_return = RET_UNKNOWN;
    //imu_init();

    led_rgb_set(50,0,100);

    // Commented out the CAN code since it has some while loops which hang if it is not connected.

//    can_state.init_return = RET_UNKNOWN;
//    can_init();

    timer_state.prev_systime = 0;
    timer_state.systime = 0;
    P7_RB4 = 0;
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
//                LED_1 = 1;
//                LED_2 = 1;
//                LED_3 = 1;
//                LED_4 = 1;
                rf_tick(1);
                if(timer_state.systime&0b100){
                    memcheck();
                }
                if(imu_state.init_return==RET_OK){
                    imu_read_state();
                }
                if(can_state.init_return==RET_OK){
                    can_process();

//                    if(can_state.is_master){
//                        if(timer_state.systime==2000){
//                            //test reset slaves
//                            can_reset_node(2);
//                        }
//                    }
                    if(timer_state.systime&0b100000000){
                        can_push_state();
                    }
                }

                led_update();

//                if(timer_state.systime==100 && rf_state.cur_network_status != INIT_SUCCESS)
//                {
//                    char* at_id = "superball";//
//                    xbee_at_cmd("ID",at_id,strlen(at_id),0,&rf_state.at_packet,0,0,0);
//                    xbee_send_at_cmd();
//                }
//                else if(timer_state.systime==120 && rf_state.cur_network_status != INIT_SUCCESS)
//                {
//                    at_parm_test[0] = 2;
//                    xbee_at_cmd("EE",at_parm_test,1,0,&rf_state.at_packet,0,0,0);
//                    xbee_send_at_cmd();
//                }else if(timer_state.systime==140 && rf_state.cur_network_status != INIT_SUCCESS)
//                {
//                    char* at_pk = "e79aa046f7190e8b"; //e79aa046f7190e8b
//                    xbee_at_cmd("PK",at_pk,strlen(at_pk),0,&rf_state.at_packet,0,0,0);
//                    xbee_send_at_cmd();
//                }
//                else if(timer_state.systime==200 && rf_state.cur_network_status != INIT_SUCCESS)
//                {
//                    xbee_at_cmd("AI",at_parm_test,0,0,&rf_state.at_packet,0,join_cb,10000);
//                    xbee_send_at_cmd();
//                }
//                else if (rf_state.cur_network_status == INIT_SUCCESS){
//                    if(http_state.init_return==RET_UNKNOWN){
//                        http_init();
//                    } else if(http_state.init_return==RET_OK){
//                        http_process();
//                    }
//                    if(!once){
//                        iptest_init();
//                        once = 1;
//                    }
//                }

                if(timer_state.systime%25 == 0){
                   LED_4=!LED_4;
                   LED_1=!LED_1;
                }
//                if(timer_state.systime&0b100000000 ){
//                    if(rf_state.cur_network_status == INIT_SUCCESS){
//                        led_rgb_set(0,255,0);
//                    } else {
//                        led_rgb_set(0,0,255);
//                    }
//
//                   }

                if(timer_state.systime%10 == 0){
                    uart_tx_packet = uart_tx_cur_packet();
                    uart_tx_packet[0] = i++;//counting
                    uart_tx_packet[1] = 0xFF;//CMD
                    uart_tx_packet[2] = 14;
                    //uart_tx_packet[3] = loadcell_state.sg_data_0;
                    uart_tx_packet[3] = (loadcell_state.values[0]>>18)&0xFF;
                    //uart_tx_packet[3] = 0xFF;
                    uart_tx_packet[4] = (loadcell_state.values[0]>>10)&0xFF;
                    //uart_tx_packet[4] = 0xFF;
                    uart_tx_packet[5] = (loadcell_state.values[0]>>2)&0xFF;
                    //uart_tx_packet[5] = 0xFF;
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

//                if(timer_state.systime&0b10000 ){
//                            uart_tx_packet = uart_tx_cur_packet();
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
                            
//
//                            if((motor_cmd_state[0].mode&0b01111111)==1){
//                                //position control: PID
//                                static UNS32 integral = 0;
//                                static UNS32 preError = 0;
//                                static UNS32 derivative = 0;
//                                uint16_t vmax = 0x540;
//                                uint16_t vmin = 0x29F;
//                                int32_t current_error = 0;
//                                int32_t pidTerm = 0;
//
//                                current_error = (int32_t)motor_cmd_state[0].position;
//                                current_error /= 1024;
//                                current_error-= motor_cmd_state[0].cur_pos/1024;
//                                integral += current_error;
//                                derivative = current_error - preError;
//
//                                pidTerm = (current_error*motor_cmd_state[0].p)
//                                        + (motor_cmd_state[0].i*integral)
//                                        + (motor_cmd_state[0].d*derivative);
//
//                                motor_cmd_state[0].dir = (pidTerm < 0);
//
//                                UNS32 abs_pidTerm = labs(pidTerm);
//                                abs_pidTerm >>= 12;
//                                abs_pidTerm += vmin;
//                                if(abs_pidTerm>vmax){
//                                    abs_pidTerm = vmax;
//                                }
//                                uart_tx_packet[3] = 0b10000 | (motor_cmd_state[0].mode&0b10000000) | (motor_cmd_state[0].brake<<3) | (motor_cmd_state[0].coast<<2) |(motor_cmd_state[0].dir<<1)|(motor_cmd_state[0].decay_mode);
//                                uart_tx_packet[4] = (abs_pidTerm>>8)&0xFF;//PWM
//                                uart_tx_packet[5] = abs_pidTerm&0xFF;
//
//                                preError = current_error;
//                            } else if((motor_cmd_state[0].mode&0b01111111)==2) {
//                                //pwm control based on load cell input
//
//                                uint32_t current_torque = loadcell_state.values[3];
//                                current_torque-=35000;
//                                static uint32_t torque_pwm = 0; //current PWM output
//                                uint16_t vmax = 0x540;
//                                uint16_t vmin = 0x29F;
//
//                                torque_pwm = current_torque;
//
//                                UNS32 abs_pidTerm = torque_pwm;
//                                abs_pidTerm /= 24;
//                                abs_pidTerm += vmin;
//                                if(abs_pidTerm>vmax){
//                                    abs_pidTerm = vmax;
//                                }
//                                uart_tx_packet[3] = 0b10000 | (motor_cmd_state[0].mode&0b10000000) | (motor_cmd_state[0].brake<<3) | (motor_cmd_state[0].coast<<2) |(motor_cmd_state[0].dir<<1)|(motor_cmd_state[0].decay_mode);
//                                uart_tx_packet[4] = (abs_pidTerm>>8)&0xFF;//PWM
//                                uart_tx_packet[5] = abs_pidTerm&0xFF;
//
//                            }
//                            else if((motor_cmd_state[0].mode&0b01111111)==3) {
//                                //constant torque mode
//                                int32_t current_torque = loadcell_state.values[2];
//                                int32_t target_torque = motor_cmd_state[0].position;
//
//                                int32_t torque_error;
//                                torque_error = current_torque;
//                                torque_error-=target_torque;
//
//                                static int32_t torque_integral = 0;
//
//                                int32_t torque_pwm;
//
////                                if(torque_error>0){
////                                    torque_pwm++;
////                                } else {
////                                    torque_pwm--;
////                                }
//                                //torque_pwm += torque_error/1000;
//                                int16_t vmax = 0x330;//0x540;
//                                int16_t vmin = 0x29F;
//                                //torque_integral += torque_error/motor_cmd_state[0].p;
//                                torque_integral = torque_error/motor_cmd_state[0].p;
//
//                                if(torque_integral>vmax-vmin){
//                                    torque_integral = vmax-vmin;
//                                } else if(torque_integral <-(vmax-vmin)) {
//                                    torque_integral = -(vmax-vmin);
//                                    //torque_integral = -torque_integral;
//                                }
//
//                                if(torque_integral<0){
//                                    torque_pwm = torque_integral;
//                                    motor_cmd_state[0].dir = 1;
//
//                                } else {
//                                    torque_pwm = torque_integral;
//                                    motor_cmd_state[0].dir = 0;
//                                }
//
//
//
//                                motor_cmd_state[0].dir = 1;//(torque_pwm<0);
//
//                                UNS32 abs_pidTerm = labs(torque_pwm);
//
//                                abs_pidTerm += vmin;
//                                if(abs_pidTerm>vmax){
//                                    abs_pidTerm = vmax;
//                                }
//                                uart_tx_packet[3] = 0b10000 | (motor_cmd_state[0].mode&0b10000000) | (motor_cmd_state[0].brake<<3) | (motor_cmd_state[0].coast<<2) |(motor_cmd_state[0].dir<<1)|(motor_cmd_state[0].decay_mode);
//                                uart_tx_packet[4] = (abs_pidTerm>>8)&0xFF;//PWM
//                                uart_tx_packet[5] = abs_pidTerm&0xFF;
//
//                            }
//                            else  {
//                                uart_tx_packet[3] = 0b10000 | (motor_cmd_state[0].mode&0b10000000) | (motor_cmd_state[0].brake<<3) | (motor_cmd_state[0].coast<<2) |(motor_cmd_state[0].dir<<1)|(motor_cmd_state[0].decay_mode);
////                            uart_tx_packet[3] = 0b10110 | (0<<3);
//                                uart_tx_packet[4] = motor_cmd_state[0].vel>>8;//0xFF;//PWM
//                                uart_tx_packet[5] = motor_cmd_state[0].vel&0xFF;//0xFF;
//                            }

//                            uart_tx_packet[6] = motor_cmd_state[0].torque>>8;//0xFF;//TORQUE
//                            uart_tx_packet[7] = motor_cmd_state[0].torque&0xFF;
////                            uart_tx_packet[4] = 0x1;//PWM
////                            uart_tx_packet[5] = 0xFF;//0xFF;
////                            uart_tx_packet[6] = 0x1;//TORQUE
////                            uart_tx_packet[7] = 0xFF;
//                            uart_tx_packet[8] = 0b00000;
//                            uart_tx_packet[9] = 0x0;//PWM
//                            uart_tx_packet[10] = 0x0;
//                            uart_tx_packet[11] = 0x0; //TORQUE
//                            uart_tx_packet[12] = 0x0;
//                            uart_tx_packet[13] = (timer_state.systime&0b100000)>0; //LED
//                            uart_tx_packet[14] = 1; //RESET

                            //led_rgb_set(0,255,100);
//                        }   
        } else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop
            if(!T1CONbits.TON){
                RGB_RED = 0;
                RGB_GREEN = RGB_BLUE = 1;
                while(1);

            }


            //memcheck();
            if(rf_state.init_return==RET_OK){
                rf_process();
            }
            if(can_state.init_return==RET_OK){
                can_time_dispatch();
            }


            //memcheck();

            uart_rx_packet = uart_rx_cur_packet();
        if (uart_rx_packet != 0) {
            //led_toggle();
//            if(uart_rx_packet[0]==0xFF){
////                uart_tx_packet[1] = 0xFF; //CMD
////                uart_tx_packet[2] = 10;
////                //transmit current position and speed
////                uart_tx_packet[3] = mdv1->pos_cnt>>8;
////                uart_tx_packet[4] = mdv1->pos_cnt&0xFF;
////                uart_tx_packet[5] = ((uint16_t)mdv1->current_speed)>>8;
////                uart_tx_packet[6] = ((uint16_t)mdv1->current_speed)&0xFF;
////                uart_tx_packet[7] = mdv2->pos_cnt>>8;
////                uart_tx_packet[8] = mdv2->pos_cnt&0xFF;
////                uart_tx_packet[9] = ((uint16_t)mdv2->current_speed)>>8;
////                uart_tx_packet[10] = ((uint16_t)mdv2->current_speed)&0xFF;
//
//                uint8_t* cp = &motor_cmd_state[0].cur_pos;
//                cp[0]=uart_rx_packet[2];
//                cp[1]=uart_rx_packet[3];
//                cp[2]=uart_rx_packet[4];
//                cp[3]=uart_rx_packet[5];
//                cp = &motor_cmd_state[0].cur_vel;
//                cp[0]=uart_rx_packet[6];
//                cp[1]=uart_rx_packet[7];
//                if(motor_cmd_state[0].cur_vel!=0){
//                    LED_2=1;
//                }
//
//            }
            uart_rx_packet_consumed();

        }

        }
    }
    return (EXIT_SUCCESS);
}

