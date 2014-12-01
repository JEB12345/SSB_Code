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
#include "power_spi.h"
#include "superball_communication.h"
#include "power_objdict.h"
#include "nRF24L01/src/nrf24l01.h"
#include <p33Exxxx.h>

/*******************************************
 * This switches the board between reciever(default) or transmitter
 * for the nRF device: #define TRANSMITTER
 ******************************************/
#define TRANSMITTER

extern timer_data timer_state;
extern analog_data adc_values;
extern can_data can_state;
extern uint8_t txreq_bitarray;

/*
 * 
 */
int
main (int argc, char** argv)
{

  // Init Function Calls
  clock_init ();
  pin_init ();
  enable_pins_init ();
  timers_init ();
  init_adc ();
  uart_init ();
  init_RF_spi ();

  // Parameter Initalziations
  timer_state.prev_systime = 0;
  timer_state.systime = 0;
  uint16_t timeStep = 50;
  volatile uint8_t* uart_tx_packet = 0;
  volatile uint8_t* uart_rx_packet = 0;
  char buzzerOn = OFF;
  unsigned char testTXpayload[1];
  unsigned char testRXpayload[1];

  EN_OUT_1 = 1;
  EN_OUT_2 = 1;
  EN_OUT_3 = 0;
  EN_OUT_4 = 0;

  BUZZER = 0;

  //Enable Motor Current Sensing
  EN_MOTOR_CURRENT = ON;
  // Def for Old board version 1
#ifdef OLD_BOARD
  VMOTOR_EN = 1;
#endif

#ifdef TRANSMITTER
  init_RF_device_TX ();
  testTXpayload[0] = 0xAB;
#else
  init_RF_device_RX ();
  //	nrf24l01_set_as_rx(true);
  //	nrf24l01_flush_rx();
  testRXpayload[0] = 0x00;
#endif

  // Enable CAN after calling the EN_OUT_# commands.
  // This prevents the while loop in the can_init() from stalling.
  can_state.init_return = RET_UNKNOWN;
  if (can_init ())
    {
      while (1);
    }

  for (;;)
    {
      if (timer_state.systime != timer_state.prev_systime)
        {
          timer_state.prev_systime = timer_state.systime;

          /**
           * Buzzer for audio notifications
           * 1kHz is the highest freq. at the moment
           */
          if (buzzerOn)
            {
              if (timer_state.systime % 1 == 0)
                {
                  BUZZER = !BUZZER;
                }
            }

          if (timer_state.systime % 100 == 0)
            {
#ifdef TRANSMITTER
              nrf24l01_irq_clear_all ();
              nrf24l01_write_tx_payload (testTXpayload, 1, true);
#else
              if (nrf24l01_irq_rx_dr_active () == true)
                {
                  nrf24l01_read_rx_payload (testRXpayload, 1);
                  nrf24l01_clear_ce ();
                  nrf24l01_irq_clear_all ();
                  nrf24l01_set_ce ();
                }
              nrf24l01_irq_clear_all ();
#endif
            }

          /**
           * This loop is for UART transmission
           */
          if (timer_state.systime % 100 == 0)
            {

              uart_tx_packet[3] = (Strain_Gauge1 >> 24)&0xFF;
              uart_tx_packet[4] = (Strain_Gauge1 >> 16)&0xFF;
              uart_tx_packet[5] = (Strain_Gauge1 >> 8)&0xFF;
              uart_tx_packet[6] = (Strain_Gauge1)&0xFF;

              uart_tx_packet[7] = 0x89;

#ifdef TRANSMITTER
              //				uart_tx_packet[8] = (Strain_Gauge2 >> 24)&0xFF;
              //				uart_tx_packet[9] = (Strain_Gauge2 >> 16)&0xFF;
              //				uart_tx_packet[10] = (Strain_Gauge2 >> 8)&0xFF;
              //				uart_tx_packet[11] = (Strain_Gauge2)&0xFF;
              uart_tx_packet[8] = testTXpayload[0];
#else
              uart_tx_packet[8] = testRXpayload[0];
#endif
              uart_tx_compute_cks (uart_tx_packet);
              uart_tx_update_index ();
              uart_tx_start_transmit ();

            }

          /**
           * This loop process all CAN and CANFestival code
           */
          if (can_state.init_return == RET_OK)
            {
              can_process ();

              if (can_state.is_master)
                {
                  if (timer_state.systime == 2000)
                    {
                      //test reset slaves
                      //can_reset_node(2);
                    }
                }
              if (timer_state.systime % timeStep == 0)
                {
                  can_push_state ();
                }
              if (timer_state.systime % 1 == 0)
                {
                  if (txreq_bitarray & 0b00000001 && !C1TR01CONbits.TXREQ0)
                    {
                      C1TR01CONbits.TXREQ0 = 1;
                      txreq_bitarray = txreq_bitarray & 0b11111110;
                    }
                  if (txreq_bitarray & 0b00000010 && !C1TR01CONbits.TXREQ1)
                    {
                      C1TR01CONbits.TXREQ1 = 1;
                      txreq_bitarray = txreq_bitarray & 0b11111101;
                    }
                  if (txreq_bitarray & 0b00000100 && !C1TR23CONbits.TXREQ2)
                    {
                      C1TR23CONbits.TXREQ2 = 1;
                      txreq_bitarray = txreq_bitarray & 0b11111011;
                    }
                  if (txreq_bitarray & 0b00001000 && !C1TR23CONbits.TXREQ3)
                    {
                      C1TR23CONbits.TXREQ3 = 1;
                      txreq_bitarray = txreq_bitarray & 0b11110111;
                    }
                  if (txreq_bitarray & 0b00010000 && !C1TR45CONbits.TXREQ4)
                    {
                      C1TR45CONbits.TXREQ4 = 1;
                      txreq_bitarray = txreq_bitarray & 0b11101111;
                    }
                  if (txreq_bitarray & 0b00100000 && !C1TR45CONbits.TXREQ5)
                    {
                      C1TR45CONbits.TXREQ5 = 1;
                      txreq_bitarray = txreq_bitarray & 0b11011111;
                    }
                  if (txreq_bitarray & 0b01000000 && !C1TR67CONbits.TXREQ6)
                    {
                      C1TR67CONbits.TXREQ6 = 1;
                      txreq_bitarray = txreq_bitarray & 0b10111111;
                    }
                }
              can_time_dispatch ();
            }
        }
      else
        { //Everything else that needs to run faster than 1ms goes in the else statement

          /*******************************************************************
           * Software controlled switching between VBAT_5V5 and VBACKUP_5V5
           *
           ******************************************************************/
          if ((adc_values.AN7) > 0x0960)
            {
              VBAT_5V5_EN = ON;
              EN_BACKUP_5V5 = OFF;
              EN_VBAT_5V5 = ON;
              LED_STATUS = OFF;
              //Enable Motor Output
              KILLSWITCH_uC = ON;
            }
          else
            {
              EN_BACKUP_5V5 = ON;
              EN_VBAT_5V5 = OFF;
              VBAT_5V5_EN = OFF;
              LED_STATUS = ON;
              //Diables Motor Output
              KILLSWITCH_uC = OFF;
              //				buzzerOn = ON;
            }

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
