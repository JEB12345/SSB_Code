/* 
 * File:   main.c
 * Author: ken and Jonathan
 *
 * Created on August 28, 2013, 11:31 PM
 * Latest Modification: 1 Sept, 2014
 */

#include "clock.h"
#include "sensor_can.h" //always include first, as this sets a number of config variables
#include "sensor_adc.h"
#include "sensor_led.h"
#include "sensor_loadcell.h"
#include "sensor_pindefs.h"
#include "sensor_state.h"
#include "sensor_memdebug.h"
#include "sensor_uart.h"
#include "Uart2.h"
#include "sensor_timers.h"
#include "sensor_memdebug.h"
#include "../libs/dspic_CanFestival/CanFestival-3/include/dspic33e/can_dspic33e.h"
#include "motor_control.h"
#include "packing.h"

/**
 * This is code from the git submodule for the MPU60xx library
 */
#include "MPU60xx/I2CdsPIC.h"
#include "MPU60xx/IMU.h"
#include "MPU60xx/IMU_Math.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <p33Exxxx.h>

extern system_data system_state;
extern timer_data timer_state;
extern loadcell_data loadcell_state;
extern imu_data imu_state;
extern can_data can_state;
extern uint8_t txreq_bitarray;

MPU6050_Data mpuData;
MAG3110_Data magData;
IMU_Data imuData;
float quaterion[4] = {0, 0, 0, 0};
float ypr[3] = {0, 0, 0};

char hex2char (char halfhex);

/*
 * 
 */
int
main (int argc, char** argv)
{
  uint32_t led_colors = 0;
  uint8_t at_parm_test[10];
  unsigned once;
  uint32_t i = 0;
  uint8_t flag = 0;
  uint8_t* uart_tx_packet = 0;
  uint8_t* uart_rx_packet;
  uint32_t old_loadcell_data;
  uint16_t timeStep = 50;

  clock_init ();
  pin_init ();
  led_init ();
  timers_init ();
  state_init ();
  uart_init ();

  // Set up UART2 for 115200 baud. There's no round() on the dsPICs, so we implement our own.
  double brg = (double) 140000000 / 2.0 / 16.0 / 115200.0 - 1.0;
  if (brg - floor (brg) >= 0.5)
    {
      brg = ceil (brg);
    }
  else
    {
      brg = floor (brg);
    }
  Uart2Init (brg); // Init UART 2 as 115200 baud/s

  loadcell_init ();
  loadcell_start ();

  IMU_Init (400000, 70000000);

  led_rgb_off ();
  led_rgb_set (50, 0, 100);

  can_state.init_return = RET_UNKNOWN;
  if (can_init ())
    {
      while (1);
    }

  timer_state.prev_systime = 0;
  timer_state.systime = 0;

  // Start Reading the int pin on IMU
  mpuData.startData = 1;

  for (;;)
    {
      if (timer_state.systime != timer_state.prev_systime)
        {
          timer_state.prev_systime = timer_state.systime;
          //everything in here will be executed once every ms
          //make sure that everything in here takes less than 1ms
          //useful for checking state consistency, synchronization, watchdog...

          led_update ();

          if (timer_state.systime % 10 == 1)
            {
              IMU_GetQuaternion (quaterion);
              QuaternionToYawPitchRoll (quaterion, ypr);
            }

          if (timer_state.systime % 5 == 1)
            {
              // Run AHRS algorithm
              IMU_UpdateAHRS (&imuData);

              //				// Run IMU algorithm (does not use MAG data)
              //				IMU_UpdateIMU(&imuData);
            }

          /**
           * CANFestival Loop
           */
          if (can_state.init_return == RET_OK)
            {
              can_process ();

              /**
               * Motor Position Testing Loop
               */
              if (timer_state.systime % 1000 == 0)
                {
                  LED_4 = !LED_4;
                  //                  Target_position = i;
                  //                  if (!flag)
                  //                    {
                  //                      if (i >= 3000)
                  //                        {
                  //                          flag = 1;
                  //                        }
                  //                      else
                  //                        {
                  //                          i += 100;
                  //                        }
                  //                    }
                  //                  else
                  //                    {
                  //                      if (i <= 100)
                  //                        {
                  //                          flag = 0;
                  //                        }
                  //                      else
                  //                        {
                  //                          i -= 100;
                  //                        }
                  //                    }
                  //                  if (i)
                  //                    {
                  //                      Target_position = 1000;
                  //                    }
                  //                  else
                  //                    {
                  //                      Target_position = 0;
                  //                    }
                  //                  i = !i;
//                  Target_position = 3000;
                }

              /**
               * Sets CANFestival shared variables
               * specific to Sensor Board
               */
              if (timer_state.systime % timeStep == 0)
                {
                  can_push_state ();
                }

              /**
               * Handles CAN transmission buffers
               */
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

          /**
           * Blinking LED Loop
           */
          if (timer_state.systime % 25 == 0)
            {
              //				LED_4 = !LED_4;
              LED_1 = !LED_1;
            }

          /**
           * Tension Controller Loop
           */
          if (timer_state.systime % 1 == 0)
            {
              Target_Tension = impedance_controller (Position_actual_value, Velocity_actual_value);
            }

          /**
           * UART Message Loop
           */
          if (timer_state.systime % 10 == 0)
            {
              uint8_t numChar;
              uint8_t uart2Data[100];
              uart_tx_packet = uart_tx_cur_packet ();
              //				numChar = sprintf(uart2Data, "%f, %f, %f, %f, %f, %f, %f, %f, %f\n",
              //					imuData.accelX, imuData.accelY, imuData.accelZ, imuData.gyroX, imuData.gyroY, imuData.gyroZ, imuData.magX, imuData.magY, imuData.magZ);
              //				numChar = sprintf(uart2Data, "%f,%f,%f\n",
              //					ypr[0], ypr[1], ypr[2]);
              //				numChar = sprintf(uart2Data, "%f,%f,%f,%f\n",
              //					quaterion[0], quaterion[1], quaterion[2], quaterion[3]);
              QuaternionToString (quaterion, uart2Data);

              Uart2WriteData (uart2Data, numChar);
              Uart2WriteData (uart2Data, 37);
              //

	      uint32_t tempLoadcellData = loadcell_state.values[0];

              uart_tx_packet = uart_tx_cur_packet ();
              uart_tx_packet[0] = 0xFF; //ALWAYS 0xFF
              uart_tx_packet[1] = 0xFF; //CMD
              uart_tx_packet[2] = 14;
//              uart_tx_packet[3] = (loadcell_state.values[0] >> 16)&0xFF;
//              uart_tx_packet[4] = (loadcell_state.values[0] >> 8)&0xFF;
//              uart_tx_packet[5] = (loadcell_state.values[0]) & 0xFF;
	      uart_tx_packet[3] = (tempLoadcellData >> 16)&0xFF;
              uart_tx_packet[4] = (tempLoadcellData >> 8)&0xFF;
              uart_tx_packet[5] = (tempLoadcellData) & 0xFF;
              uart_tx_packet[6] = 0x01;
              uart_tx_packet[7] = 0x89; // same as " "
              //uart_tx_packet[8] = (loadcell_state.values[1]>>16)&0xFF;
              uart_tx_packet[8] = 0xFF;
              //uart_tx_packet[9] = (loadcell_state.values[1]>>8)&0xFF;
              uart_tx_packet[9] = 0xFF;
              //uart_tx_packet[10] = loadcell_state.values[1]&0xFF;
              uart_tx_packet[10] = 0xFF;
              uart_tx_packet[11] = 0x02;
              uart_tx_packet[12] = 0x8b; // same as "\n"
              uart_tx_compute_cks (uart_tx_packet);
              uart_tx_update_index ();
              uart_tx_start_transmit ();
            }
        }
      else
        {
          //untimed processes in main loop:
          //executed as fast as possible
          //these processes should NOT block the main loop

          if (!T1CONbits.TON)
            {
              RGB_RED = 0;
              RGB_GREEN = RGB_BLUE = 1;
              while (1);

            }

          uart_rx_packet = uart_rx_cur_packet ();
          if (uart_rx_packet != 0)
            {
              uart_rx_packet_consumed ();
            }
        }
    }
  return (EXIT_SUCCESS);
}

char
hex2char (char halfhex)
{
  char rv;
  // Test for numeric characters
  if (halfhex <= 9 && halfhex >= 0)
    {
      return (halfhex + '0');
    }// Otherwise check for upper-case A-F
	else if ((rv = halfhex - 10) <= 5 && rv >= 0) {
		return rv + 'A';
	} // Finally check for lower-case a-f
	// Otherwise return -1 as an error
	return -1;
}

/**
 * This is the interrupt function for the INT pin on the MPU6000
 */
void __attribute__((__interrupt__, no_auto_psv))
_CNInterrupt(void)
{
	if (mpuData.startData == 1) {
		if (PORTFbits.RF0 == 1) {
			// Gets the IMU data after the INT pin has been triggered
			IMU_GetData(&mpuData, &magData);

			// Data normilization
			IMU_normalizeData(mpuData, magData, &imuData);
		}
	}
	IFS1bits.CNIF = 0; // Clear the interrupt flag
}
