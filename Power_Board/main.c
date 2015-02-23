/* 
 * File:   main.c
 * Author: jonathan
 *
 * Created on March 20, 2014, 1:20 PM
 */

#include "power_clock.h"
#include "power_pindef.h"
#include "power_led.h"
#include "power_state.h"
#include "power_enable_pins.h"
#include "power_timers.h"
#include "power_adc.h"
#include "power_can.h"
#ifdef ID_3
#include "power_objdict_3.h"
#else
#include "power_objdict_73.h"
#endif
#include "power_nrf24l01.h"
#include "power_buzzer.h"
#include "power_i2c.h"
#include "power_temperature.h"
#include <p33Exxxx.h>

extern timer_data timer_state;
extern analog_data adc_values;
extern can_data can_state;
extern system_data system_state;
extern nrf24l01_data nrf24l01_state;

#ifndef IS_KILLSWITCH
int main (int argc, char** argv)
{
  state_init();
#ifdef ID_3
  system_state.system_id = 0x03;
#else
  system_state.system_id = 0x73;
#endif
  
  // Init Function Calls
  clock_init ();
  pin_init ();
  enable_pins_init ();
  //5V5 Output Control Pins (make sure the BBB doesn't reboot)
  EN_OUT_1 = 1; //Default outputs
  EN_OUT_2 = 1;
  EN_OUT_3 = 0;
  EN_OUT_4 = 0;
  timers_init ();
  buzzer_init();
  buzzer_set_frequency(TONE_A_7);
  init_adc ();
  led_init ();
  buzzer_set_frequency(TONE_A_6);
  nrf24l01_init();
  buzzer_set_frequency(TONE_A_5);
  i2c_1_init();
  temperature_init();
  buzzer_set_frequency(TONE_D_5);

  // Parameter Initalziations for timer, UART
  timer_state.prev_systime = 0;
  timer_state.systime = 0;

  uint16_t buzzer_init = 1; //used to turn the buzzer off after initialization

  //Enable Motor Current Sensing
  EN_MOTOR_CURRENT = 1;
 
  // Enable CAN after calling the EN_OUT_# commands.
  // This prevents the while loop in the can_init() from stalling.

  can_state.init_return = RET_UNKNOWN;
  if (can_init()) {
        while (1) {
            buzzer_set_frequency(TONE_A_8);
        }
    }
  buzzer_set_frequency(TONE_A_4);

  LED_STATUS = ON;

  //TODO: make sure the modulo operations don't hurt performance
  for (;;){
      if (timer_state.systime != timer_state.prev_systime)
        {
          timer_state.prev_systime = timer_state.systime;
          asm("CLRWDT"); //clear watchdog timer
          
          //buzzer stuff
          if(timer_state.systime==250 && buzzer_init){
              buzzer_set_frequency(0);//turn buzzer off
              buzzer_init = 0;
          }
          buzzer_update();
          if(!KILLSWITCH_nFAULT){
            //fault detected (overcurrent) by the mosfet driver!
            //what do we do now?
              if(timer_state.systime%500==0){
                buzzer_set_frequency(TONE_A_7);
              } else if(timer_state.systime%500==250){
                  buzzer_set_frequency(0);
              }
          }

          nrf24l01_update();
          nrf24l01_check_killswitch();
          if(nrf24l01_state.init_return != RET_OK){
              buzzer_set_frequency(TONE_B_8);
          }

          if(timer_state.systime%123==0){
              temperature_update();
          }

          /**
           * This loop processes all CAN and CANFestival code
           */
          can_update();

          adc_update_state();

          //kill switch PIC watchdog
          uC_KS_1 = !uC_KS_1;
        }

      else { //Everything else that needs to run faster than 1ms goes in the else statement

          /*******************************************************************
           * Software controlled switching between VBAT_5V5 and VBACKUP_5V5
           *
           ******************************************************************/
          adc_update_output();

          /*****************************************************************
           *
           * Battery charger
           *
           *****************************************************************/
          if(EN_BACKUP_5V5){
              VBACKUP_CHARGER_DISABLE;
          } else {
              VBACKUP_CHARGER_ENABLE;
          }
          
          //LEDs
          if(VMOTOR_EN){
              LED_R = 1;
              LED_G = 0;
            } else {
              LED_R = 0;
              LED_G = 1;
            }
          if(EN_BACKUP_5V5) {
              LED_B = 0;
          } else {
              LED_B = 1;
          }
          if(timer_state.fasttime<5000){
              LED_STATUS = ON;
          } else {
              LED_STATUS = OFF;
          }
      }

    }

}
#else

#define KS_SEND_SWITCHSTATE_PERIOD  25  //send KS state every N ms
#define KS_SEND_SWITCHSTATE_OFFSET  0   //offset in ms (try not to send two packets at almost the same time)
#define KS_SEND_SYNC_EVERY          10   //set the sync bit in every Nth KS state packet
#define KS_SEND_BROADCAST_PERIOD    200 //send broacast every N ms
#define KS_SEND_BROADCAST_OFFSET    13
int main (int argc, char** argv)
{
  state_init();
  system_state.system_id = 0x0;

  // Init Function Calls
  clock_init ();
  pin_init ();
  enable_pins_init ();
  timers_init ();
  buzzer_init();
  init_adc ();
  led_init ();
  nrf24l01_init();

  // Parameter Initalziations for timer, UART
  timer_state.prev_systime = 0;
  timer_state.systime = 0;

  EN_OUT_1 = 1;
  EN_OUT_2 = 1;
  EN_OUT_3 = 1;
  EN_OUT_4 = 1;

  LED_STATUS = ON;

  LED_R = 0;
  LED_G = 1;
  LED_B = 1;

  uint16_t kill_state = KILL_ALL_OFF;

  //TODO: make sure the modulo operations don't hurt performance
  for (;;){
      if (timer_state.systime != timer_state.prev_systime)
        {
          timer_state.prev_systime = timer_state.systime;
          uC_KS_1 = !uC_KS_1;

          //reset status led
//          if(timer_state.systime%100==0){
//              LED_STATUS = ON;
//          } else if(timer_state.systime%100==50){
//              LED_STATUS = OFF;
//          }


          nrf24l01_update();

          uint16_t i;
          static uint16_t sync_ctr = 0;
          //use this to send kill switch + sync data (1 byte)
          if(timer_state.systime%KS_SEND_SWITCHSTATE_PERIOD==KS_SEND_SWITCHSTATE_OFFSET){
              nrf24l01_tx_packet* tx_pkt;
              tx_pkt = nrf24l01_tx_cur_packet();
              memset(tx_pkt->data,0,sizeof(tx_pkt->data)); //not really needed, but useful for debugging
              if(kill_state==KILL_ALL_ON){
                  tx_pkt->data[0] = 0b11;
              } else {
                  tx_pkt->data[0] = 0b10;
              }
              if(sync_ctr++>=KS_SEND_SYNC_EVERY){
                  sync_ctr = 0;
                  tx_pkt->data[0] |= KILL_SYNC;
                  LED_STATUS = ON;
              } else {
                  LED_STATUS = OFF;
              }
              tx_pkt->data_length = 1;
              tx_pkt->address_length = 3;
              tx_pkt->address[0] = 0x12;
              tx_pkt->address[1] = 0x34;
              tx_pkt->address[2] = 1;

              nrf24l01_tx_update_index();
              uC_KS_2 = !uC_KS_2;
          }

          //use this to broadcast data (32 bytes)
          if(timer_state.systime%KS_SEND_BROADCAST_PERIOD==KS_SEND_BROADCAST_OFFSET){
              nrf24l01_tx_packet* tx_pkt;
              tx_pkt = nrf24l01_tx_cur_packet();
              for(i=0;i<32;++i){
                tx_pkt->data[i] = i;
              }
              tx_pkt->data_length = 32;
              tx_pkt->address_length = 3;
              tx_pkt->address[0] = 0xB0;
              tx_pkt->address[1] = 0x0B;
              tx_pkt->address[2] = 3;

              nrf24l01_tx_update_index();
          }

          switch(kill_state) {
                case KILL_ALL_OFF:
                    if (timer_state.systime % 500 == 0) {
                        buzzer_set_frequency(TONE_A_6);
                    } else if (timer_state.systime % 500 == 250) {
                        buzzer_set_frequency(0);
                    }
                    break;
                case KILL_ALL_ON:
                    if (timer_state.systime % 10 == 0){
                        buzzer_set_frequency(0);
                    }
                  break;
              default:
                  break;
          };

          adc_update_state();

        }
      else { //Everything else that needs to run faster than 1ms goes in the else statement

          /*******************************************************************
           * Software controlled switching between VBAT_5V5 and VBACKUP_5V5
           *
           ******************************************************************/
          adc_update_output();
          KILLSWITCH_uC = 1;
          if(EN_BACKUP_5V5){
              VBACKUP_CHARGER_DISABLE;
          } else {
              VBACKUP_CHARGER_ENABLE;
          }
          if(VMOTOR_EN){
              LED_G = 0;
              LED_R = 1;
              kill_state = KILL_ALL_ON;
          } else {
              LED_G = 1;
              LED_R = 0;
              kill_state = KILL_ALL_OFF;
          }

        }
    }

}
#endif
