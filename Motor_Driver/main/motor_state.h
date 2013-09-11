/* 
 * File:   sensor_state.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:55 PM
 */

#ifndef SENSOR_STATE_H
#define	SENSOR_STATE_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {
        RET_OK = 0,
        RET_ERROR = 1,
        RET_UNKNOWN = 127
    }
    return_value_t;

    typedef enum {
        UART_RX_STATE_INIT = 0,
        UART_RX_STATE_CMD = 1,
        UART_RX_STATE_LEN = 2,
        UART_RX_STATE_DATA = 3,
        UART_RX_STATE_CKS = 4
    } uart_rx_state_t;

#define UART_TX_PACKET_BUFF_LEN 10
#define UART_TX_PACKET_MAX_LEN 50
#define UART_RX_PACKET_BUFF_LEN 10
#define UART_RX_PACKET_MAX_LEN 32
#define WATCHDOG_TIMEOUT 500

     /**
     * Th state machine for the ADC SPI
     */
    typedef enum  {
        DMA_SPI_LC_IDLE, ///< No reading is being performed.
        DMA_SPI_LC_WRITING_RESET,
        DMA_SPI_LC_WAITING_500us,
        DMA_SPI_LC_WAITING_TO_WRITE_SETTINGS,
        DMA_SPI_LC_WRITING_SETTINGS,
        DMA_SPI_LC_WRITING_INSTRUCTION_2,
        DMA_SPI_LC_WRITING_INSTRUCTION_3,
        DMA_SPI_LC_WAITING_FOR_READOUT,
        DMA_SPI_LC_READING_DEVICES, //We are actually reading the data from the devices
        DMA_SPI_LC_DATA_READY_TO_BE_PROCESSED // We have finished to read the data, and we need to process it to extract actual data in the spi_main function
    } DMA_SPI_LC_state_t;


    //maintain all state variables here
    typedef struct {
        return_value_t          init_return;
        int volatile            state;
    } imu_data;
    
    typedef struct {
        return_value_t          init_return;
        volatile struct {
          uint16_t AN6;
          uint16_t AN7;
          uint16_t AN8;
          uint16_t AN11;
        } values;
    } adc_data;

    typedef struct {
        return_value_t          init_return;
        int volatile            state;
    } can_data;

    typedef struct {
        return_value_t          init_return;
        uint8_t                 led_intensities[4];
    } led_data;

    typedef struct {
        return_value_t          init_return;
        int volatile            state;
        uint32_t volatile       values[4];
        char volatile           raw_data_0[3]; //raw data bytes of last packet
        char volatile           raw_data_1[3]; //need not be a valid packet
        char volatile           raw_data_2[3];
        char volatile           raw_status[3];
        DMA_SPI_LC_state_t volatile     int_state;
        uint8_t volatile           data_ready; //data available was signalled by ADC

    } loadcell_data;

    typedef struct {
        return_value_t          init_return;
        int volatile            state;
    } rf_data;

    typedef struct {
        return_value_t          init_return;
        uint32_t volatile       systime; //updated by a timer
        uint32_t                prev_systime;  //updated in main loop
    } timer_data;

    typedef enum {STATE_UNKNOWN = 0, STATE_INITIALIZED = 1, STATE_ERROR = 127} state_t;
    typedef struct {
        return_value_t          init_return;
        uint16_t                ticks_since_last_cmd;
        state_t volatile        state; //system state
    } system_data;

    typedef struct {
        return_value_t          init_return;
        uint32_t                fcy;
    } clock_data;

    typedef struct {
        return_value_t          init_return;
        uint32_t                rotor_position;  //qei_data contains raw encoder data, all processed results are to be found in motor_data
        uint32_t                index;       
        //TODO: add wire length estimation
    } qei_data;

    typedef struct {
        return_value_t          init_return;
        uint8_t                 cur_state;
        uint8_t                 prev_state;
        uint16_t volatile       last_update_tmr;
        unsigned volatile       direction; //0 not moving, 1 positive, 2 negative
    } hallsensor_data;

    typedef struct {
        return_value_t          init_return;
        uint16_t volatile       rotor_position;
        uint16_t volatile       rotor_turns;
        float volatile          rotor_state;
        float volatile          rotor_state_interpolated;
        float volatile          rotor_speed; //in sectors/s (60deg/s)
        float                   wire_length;
    } motor_data;

    typedef struct {
        return_value_t          init_return;
        unsigned volatile       tx_idle;
        uint32_t volatile       bytes_sent;
        uint32_t volatile       tx_num_errors;
        uint32_t volatile       packets_sent;

        uint16_t volatile       tx_packets_start;
        uint16_t volatile       tx_packets_end;
        uint16_t volatile       tx_buffer_idx;

        volatile uint16_t tx_packets[UART_TX_PACKET_BUFF_LEN][UART_TX_PACKET_MAX_LEN];

        uart_rx_state_t volatile rx_state;
        uint32_t volatile       rx_num_errors;
        uint32_t volatile       bytes_received;

        uint16_t volatile       rx_packets_start;
        uint16_t volatile       rx_packets_end;
        uint16_t volatile       rx_buffer_idx;

        volatile uint16_t rx_packets[UART_RX_PACKET_BUFF_LEN][UART_RX_PACKET_MAX_LEN];
        volatile uint16_t*      rx_buffer;
        volatile unsigned       rx_buffer_len;
        volatile unsigned       rx_cks;
        volatile unsigned       rx_len;
        uint32_t volatile       packets_received;
    } uart_data;

    return_value_t state_init();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_STATE_H */

