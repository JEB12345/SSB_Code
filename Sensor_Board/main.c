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
#include "sensor_uart.h"
#include "sensor_timers.h"
#include "../libs/dspic_CanFestival/CanFestival-3/include/dspic33e/can_dspic33e.h"
#include "packing.h"

#ifndef ANCHOR
/**
 * This is code from the git submodule for the MPU60xx library
 */
#include "MPU60xx/I2CdsPIC.h"
#include "MPU60xx/IMU.h"
#include "MPU60xx/IMU_Math.h"
#endif

/**
 * This code is for the DWM1000 Module
 */
#include "sensor_spi2.h"
#include "dwm1000_dspic/dwm_spi.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <p33Exxxx.h>

extern volatile unsigned int ecan1TXMsgBuf[8][8] __attribute__((aligned(8 * 16)));

extern system_data system_state;
extern timer_data timer_state;
extern loadcell_data loadcell_state;
//extern imu_data imu_state;
extern can_data can_state;
extern uint8_t txreq_bitarray;
extern dwm_1000_status dwm_status;

#ifndef ANCHOR
MPU6050_Data mpuData;
MAG3110_Data magData;
//imu_data imu_state;
IMU_Data imuData;
float quaterion[4] = {0, 0, 0, 0};
float ypr[3] = {0, 0, 0};
#endif 

uint16_t count = 0;

char hex2char(char halfhex);

/*
 * 
 */
int
main(int argc, char** argv)
{    
    uint32_t led_colors = 0;
    uint8_t at_parm_test[10];
    unsigned once;
    uint32_t i = 0;
    uint8_t canPrescaler = 0;
    uint8_t* uart_tx_packet = 0;
    uint8_t* uart_rx_packet;
    uint32_t old_loadcell_data;
    uint16_t timeStep = 1;
    uint8_t dwt_init_flag = 0;
    uint8_t dwt_works = 0;
    uint8_t result = -1;

    volatile unsigned timer4_flag = 0;
    
    NFET_DWM = 1;
    uint8_t s = decamutexon();
    dwt_rxdiag_t test;
    dwt_deviceentcnts_t counters;
    
    uint32_t debug_time;

    clock_init();
    pin_init();
    led_init();
    timers_init();
    state_init();
    uart_init();

    // Needs to be called ASAP so that the DWM isn't held in reset
    //DWM_RESET_OFF;

    // Set up UART2 for 115200 baud. There's no round() on the dsPICs, so we implement our own.
//    double brg = (double) 140000000 / 2.0 / 16.0 / 115200.0 - 1.0;
//    if (brg - floor(brg) >= 0.5) {
//        brg = ceil(brg);
//    }
//    else {
//        brg = floor(brg);
//    }
    //  Uart2Init (brg); // Init UART 2 as 115200 baud/s

#ifndef ANCHOR
    loadcell_init();
    loadcell_start();


    led_rgb_off();
    led_rgb_set(50, 0, 100);
#endif

    can_state.init_return = RET_UNKNOWN;
#ifndef ANCHOR
    if (can_init()) {
        while (1);
    }
#endif

    timer_state.prev_systime = 0;
    timer_state.systime = 0;

#ifdef ANCHOR
//    ranging_id = ANCHOR_ID +1;
    ranging_id = 20;
#endif
    
#ifndef ANCHOR
    // Start Reading the int pin on IMU
    mpuData.startData = 0;
#endif 
//#if defined(CONF71) && 
#if !defined(NO_BOOTLOADER)
    if (IMU_Init(400000, 70000000) == 0) {
        mpuData.startData = 1;
    }
#endif

    for (;;) {
        if (timer_state.systime != timer_state.prev_systime) {
            timer_state.prev_systime = timer_state.systime;
            //everything in here will be executed once every ms
            //make sure that everything in here takes less than 1ms
            //useful for checking state consistency, synchronization, watchdog...
            
            if(result != 0){
#ifndef FIXED_BASE
                if(ranging_id != 0){
                    dwt_init_flag = 1;
                }
#else
                dwt_init_flag = 1;
#endif
                    if(dwt_init_flag){
                        config_spi2_slow();
#ifdef CONF71
                        result = dwm_init((ranging_id - 2), timer_4_set);
#else
#ifdef FIXED_BASE
                        result = dwm_init(0, timer_4_set);
#else
//                        if(ranging_id = 0xC){
//                            ranging_id = 0xA;
//                        }
                        result = dwm_init(ranging_id-1, timer_4_set);
#endif
#endif
                        if(result == 0){
#ifndef ANCHOR
                            LED_3 = 1;
#endif
                            dwt_works = 1;
                            config_spi2_fast();
                            instance_process();        
        //                        dwt_configeventcounters(1);
                        }
                        decamutexoff(s);
                        dwt_init_flag = 0;
                    }
            }

            if(timer_state.systime % 1 == 0){
                if(dwt_works){
                    instance_process();
//                    dwt_readeventcounters(&counters);
                }
            }

            if(timer_state.systime % 1000 == 0) {
#ifndef ANCHOR
                LED_4 = 1;
#endif
            }

            led_update();
            
#ifndef ANCHOR
            /**
             * IMU Loop
             */
            if(mpuData.startData){
                if (timer_state.systime % 10 == 0) {
    //                IMU_GetQuaternion(quaterion);
    //                QuaternionToYawPitchRoll(quaterion, ypr);
                }

                if (timer_state.systime % 5 == 0) {
                    IMU_normalizeData(&mpuData, &magData, &imuData);
                    // Run AHRS algorithm
                    //TODO: Takes a long time (and can stall the pic) ONLY when the DWM code is loaded
//                    IMU_UpdateAHRS (&imuData);

                    // Run IMU algorithm (does not use MAG data)
                    IMU_UpdateIMU(&imuData);

                    //copy state to CAN dictionary
                    IMU_CopyOutput(&imuData, &mpuData, &magData);
                }
            }
#endif

            /**
             * CANFestival Loop
             */
            if (can_state.init_return == RET_OK) {
                can_process();

                /**
                 * Sets CANFestival shared variables
                 * specific to Sensor Board
                 */
                can_push_state();
            }

            /**
             * Blinking LED Loop
             */
            if (timer_state.systime % 25 == 0) {
#ifndef ANCHOR
                              LED_1 = !LED_1;
#endif
            }
            

            /**
             * UART DW1000 debug Loop
             */
            if (timer_state.systime % 50 == 0 ) {
                //if(!(abs(dwm_status.distance[0]) > 1000)){
                    uart_tx_packet = uart_tx_cur_packet ();
                    uart_tx_packet[0] = 0xFF; //ALWAYS 0xFF
                    uart_tx_packet[1] = 0xFF; //CMD
                    uart_tx_packet[2] = 14;
                    memcpy(&(uart_tx_packet[3]),&(dwm_status.rxdiag.firstPathAmp1),2);
                    memcpy(&(uart_tx_packet[5]),&(dwm_status.rxdiag.firstPathAmp2),2);
                    memcpy(&(uart_tx_packet[7]),&(dwm_status.rxdiag.firstPathAmp3),2);
                    memcpy(&(uart_tx_packet[9]),&(dwm_status.rxdiag.maxGrowthCIR),2);
                    memcpy(&(uart_tx_packet[11]),&(dwm_status.rxdiag.rxPreamCount),2);
                    
                    uart_tx_compute_cks (uart_tx_packet);
                    uart_tx_update_index ();
                    uart_tx_start_transmit ();
                //}
            }
            
            if (timer_state.systime % 100 == 0 && dwt_works) {
                //dwm_status.irq_enable = 1; //in case the device hangs
                dwt_forcetrxoff();
//                dwt_setrxtimeout(0); //TODO: not sure if needed
                dwt_rxenable(0);
            }

        }
        else {
            //untimed processes in main loop:
            //executed as fast as possible
            //these processes should NOT block the main loop
//            LED_4 = mpuData.accelX > 0;
//            LED_3 = mpuData.accelY > 0;
//            LED_1 = mpuData.accelZ > 0;

#ifndef ANCHOR
            /**
             * IMU Fast Function
             */
            if(mpuData.startData){
                IMU_CopyI2CData(&mpuData, &magData);
            }
#endif

            if (!T1CONbits.TON) {
#ifndef ANCHOR
                RGB_RED = 0;
                RGB_GREEN = RGB_BLUE = 1;
#endif
                while (1);

            }
            
            //Manually check if the IRQ pin on the DW1000 is still high
            //to prevent getting stuck on a failed SPI read
            if((dwm_status.irq_enable==0) && (DWM_IRQ==1) && (dwt_works==1)){
                dwm_status.irq_enable=1;
            }

            if(dwm_status.irq_enable){ 
                dwm_status.irq_enable = 0;
                dwt_isr();
            }

            if(dwm_status.timer_interrupt){
                dwt_timer_interrupt();
            }
            
            if(can_flag){
                TimeDispatch();
                can_flag = 0;
            }

            uart_rx_packet = uart_rx_cur_packet();
            if (uart_rx_packet != 0) {
                uart_rx_packet_consumed();
            }

            /**
             * Handles CAN transmission buffers
             */
            if ((txreq_bitarray & 0b00000001) && !C1TR01CONbits.TXREQ0) {
                C1TR01CONbits.TXREQ0 = 1;
                txreq_bitarray = txreq_bitarray & 0b11111110;
            }
            if ((txreq_bitarray & 0b00000010) && !C1TR01CONbits.TXREQ1) {
                C1TR01CONbits.TXREQ1 = 1;
                txreq_bitarray = txreq_bitarray & 0b11111101;
            }
            if ((txreq_bitarray & 0b00000100) && !C1TR23CONbits.TXREQ2) {
                C1TR23CONbits.TXREQ2 = 1;
                txreq_bitarray = txreq_bitarray & 0b11111011;
            }
            if ((txreq_bitarray & 0b00001000) && !C1TR23CONbits.TXREQ3) {
                C1TR23CONbits.TXREQ3 = 1;
                txreq_bitarray = txreq_bitarray & 0b11110111;
            }
            if ((txreq_bitarray & 0b00010000) && !C1TR45CONbits.TXREQ4) {
                C1TR45CONbits.TXREQ4 = 1;
                txreq_bitarray = txreq_bitarray & 0b11101111;
            }
            if ((txreq_bitarray & 0b00100000) && !C1TR45CONbits.TXREQ5) {
                C1TR45CONbits.TXREQ5 = 1;
                txreq_bitarray = txreq_bitarray & 0b11011111;
            }
            if ((txreq_bitarray & 0b01000000) && !C1TR67CONbits.TXREQ6) {
                C1TR67CONbits.TXREQ6 = 1;
                txreq_bitarray = txreq_bitarray & 0b10111111;
            }
        }
    }
    return (EXIT_SUCCESS);
}

char
hex2char(char halfhex)
{
    char rv;
    // Test for numeric characters
    if (halfhex <= 9 && halfhex >= 0) {
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
_CNInterrupt(void) {
#ifndef ANCHOR
    if (mpuData.startData == 1) {
        if (PORTFbits.RF0 == 1) {
            // Gets the IMU data after the INT pin has been triggered
            IMU_GetCount(); //(&mpuData, &magData);
        }
    }
#endif
    IFS1bits.CNIF = 0; // Clear the interrupt flag
}

void Delay_us(unsigned int delay)
{
	uint16_t i;
	for (i = 0; i < delay; i++) {
		__asm__ volatile ("repeat #39");
		__asm__ volatile ("nop");
	}
}
