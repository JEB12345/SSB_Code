/* 
 * File:   main.c
 * Author: jonathan
 *
 * Created on March 20, 2014, 1:20 PM
 */

//#include "clock.h"
#include "power_clock.h"
#include "power_pindef.h"
#include "power_led.h"
#include "power_state.h"
#include "power_enable_pins.h"
#include "power_timers.h"
#include "power_adc.h"
#include "power_uart.h"
#include "power_can.h"
//#include "power_spi.h"
//#include "superball_communication.h"
#include "power_objdict.h"
//#include "nRF24L01/src/nrf24l01.h"
#include "power_nrf24l01.h"
#include "power_buzzer.h"
#include <p33Exxxx.h>

/*******************************************
 * This switches the board between receiver(default) or transmitter
 * for the nRF device: #define TRANSMITTER
 ******************************************/
//DEFINED IN CONFIGURATION

//TODO:
//  temperature sensor
//  current sensor

extern timer_data timer_state;
extern analog_data adc_values;
extern can_data can_state;
extern system_data system_state;

/*
 * 
 */
int main (int argc, char** argv)
{
  state_init();
  system_state.system_id = 0x03;//TODO: get this from the bootloader
  
  // Init Function Calls
  clock_init ();
  pin_init ();
  enable_pins_init ();
  timers_init ();
  buzzer_init();
  buzzer_set_frequency(TONE_A_7);
  init_adc ();
  uart_init ();
  led_init ();
  buzzer_set_frequency(TONE_A_6);
  
  buzzer_set_frequency(TONE_A_5);

  // Parameter Initalziations for timer, UART
  timer_state.prev_systime = 0;
  timer_state.systime = 0;
  
  unsigned char testTXpayload[1];
  unsigned char testRXpayload[1];

  uint16_t buzzer_init = 1; //used to turn the buzzer off after initialization

  //5V5 Output Control Pins
  EN_OUT_1 = 1;
  EN_OUT_2 = 1;
  EN_OUT_3 = 0;
  EN_OUT_4 = 0;

  //Enable Motor Current Sensing
  EN_MOTOR_CURRENT = 1;
  // Def for Old board version 1
#ifdef OLD_BOARD
  VMOTOR_EN = 1;
#endif

  // Enable CAN after calling the EN_OUT_# commands.
  // This prevents the while loop in the can_init() from stalling.

  can_state.init_return = RET_UNKNOWN;
  if (can_init ())
    {
      while (1);
    }
  buzzer_set_frequency(TONE_A_4);

  LED_STATUS = ON;

  //TODO: make sure the modulo operations don't hurt performance
  for (;;){
      if (timer_state.systime != timer_state.prev_systime)
        {
          timer_state.prev_systime = timer_state.systime;

          //reset status led
          if(timer_state.systime%100==0){
              LED_STATUS = ON;
          }

          //buzzer stuff
          if(timer_state.systime==250 && buzzer_init){
              buzzer_set_frequency(0);//turn buzzer off
              buzzer_init = 0;
              nrf24l01_init();
          }
          buzzer_update();

          nrf24l01_update();

          uart_update();

          /**
           * This loop processes all CAN and CANFestival code
           */
          can_update();

#ifdef TRANSMITTER
          uint16_t i;
          if(timer_state.systime%1000==500){
              nrf24l01_tx_packet* tx_pkt;
              tx_pkt = nrf24l01_tx_cur_packet();
              for(i=0;i<32;++i){
                tx_pkt->data[i] = i;
              }
              tx_pkt->data_length = 32;
              tx_pkt->address_length = 3;
              tx_pkt->address[0] = 0x12;
              tx_pkt->address[1] = 0x34;
              tx_pkt->address[2] = 1;

              nrf24l01_tx_update_index();

          }
#else
          if(nrf24l01_rx_cur_packet()){
              buzzer_set_frequency(TONE_C_7);
          }
#endif
           
        }
      else { //Everything else that needs to run faster than 1ms goes in the else statement

          /*******************************************************************
           * Software controlled switching between VBAT_5V5 and VBACKUP_5V5
           *
           ******************************************************************/
          adc_update();         

          /*******************************************************************
           * Software controlled Killswitch for power switch
           *
           * why? -> Because the PMOS does not turn off VBAT_5V5 when the main
           * power switch is flipped off. This is not ideal and will not always
           * cut power to board when VBAT_5V5 is main power source.
           ******************************************************************/
          //			if (adc_values.AN8 < 0x0800) {
          //				VBAT_5V5_EN = OFF;
          //			}
        }
    }

}
