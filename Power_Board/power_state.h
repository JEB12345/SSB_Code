/* 
 * File:   power_state.h
 * Author: ken/Jonathan
 *
 */

#ifndef POWER_STATE_H
#define	POWER_STATE_H
#include <stdint.h>
#include "superball_circularbuffer.h"

#define bool uint8_t

// Defining ON and OFF
enum {
    OFF,
    ON
 };

// Universal return values
typedef enum {
    RET_OK = 0,
    RET_ERROR = 1,
    RET_UNKNOWN = 127
} return_value_t;

// Used to init the clock
typedef struct {

    return_value_t          init_return;
    uint32_t                fcy;
} clock_data;

// Main 1ms loop timer data
typedef struct {
    return_value_t          init_return;
    unsigned int volatile   systime;        //updated by timer 1
    unsigned int            prev_systime;   //updated in main loop
    uint32_t volatile       fasttime;      //updated by timer 5: 1tick/2uS (500KHz) synced over RF
    uint32_t volatile       fasttime_irq;   
    unsigned int            prev_fasttime;  //updated in main loop
} timer_data;

// ADC data Struct for buffer
typedef struct {
    uint16_t                AN6;    //5V5 line
    uint16_t                AN7;    //main battery voltage
    uint16_t                AN8;    //backup battery voltage
    uint16_t                AN11;   //motor current
    uint16_t                AN12;   //actual motor voltage
    uint16_t                AN13;   //5V5 current

    uint32_t                mV_5V5_out;
    uint32_t                mA_5V5_out;
    uint32_t                mW_5V5_out;
    uint32_t                mV_main_battery;
    uint32_t                mV_vbackup_battery;
    int32_t                 mA_motor_current;
    uint32_t                mV_motor_voltage;
    int32_t                 mW_motor_power;

    uint8_t                 timer_trip;
}analog_data;

// UART State handlers
#define UART_TX_PACKET_MAX_LEN  50
#define UART_TX_PACKET_BUFF_LEN 10
#define UART_RX_PACKET_BUFF_LEN 10
#define UART_RX_PACKET_MAX_LEN  50


typedef enum {
    UART_RX_STATE_INIT = 0,
    UART_RX_STATE_CMD = 1,
    UART_RX_STATE_LEN = 2,
    UART_RX_STATE_DATA = 3,
    UART_RX_STATE_CKS = 4
} uart_rx_state_t;

typedef struct {
    return_value_t          init_return;
    unsigned volatile       tx_idle;
    uint32_t volatile       bytes_sent;
    uint32_t volatile       tx_num_errors;
    uint32_t volatile       packets_sent;

    uint16_t volatile       tx_packets_start;
    uint16_t volatile       tx_packets_end;
    uint16_t volatile       tx_buffer_idx;

    volatile uint8_t tx_packets[UART_TX_PACKET_BUFF_LEN][UART_TX_PACKET_MAX_LEN];

    uart_rx_state_t volatile rx_state;
    uint32_t volatile       rx_num_errors;
    uint32_t volatile       bytes_received;

    uint16_t volatile       rx_packets_start;
    uint16_t volatile       rx_packets_end;
    uint16_t volatile       rx_buffer_idx;

    volatile uint8_t rx_packets[UART_RX_PACKET_BUFF_LEN][UART_RX_PACKET_MAX_LEN];
    volatile uint8_t*      rx_buffer;
    volatile unsigned       rx_buffer_len;
    volatile unsigned       rx_cks;
    volatile unsigned       rx_len;
    uint32_t volatile       packets_received;
} uart_data;
    
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
        char                    is_master;
        int volatile            state;
        volatile bool           timer_flag;
    } can_data;

    typedef struct {
        return_value_t          init_return;
        //sets the color of the RGB led
        uint8_t                 rgb_red;
        uint8_t                 rgb_green;
        uint8_t                 rgb_blue;
    } led_data;

    typedef enum {STATE_UNKNOWN = 0, STATE_INITIALIZED = 1, STATE_ERROR = 127} state_t;
    typedef struct {
        return_value_t          init_return;
        state_t volatile state; //system state
        uint8_t             system_id;//TODO get this number from the bootloader
    } system_data;

    typedef struct {
        uint16_t address[5]; //use 16 bit fields as the SPI code assumes this
        uint8_t address_length;
        uint16_t data[32];//use 16 bit fields as the SPI code assumes this
        uint8_t data_length;
    } nrf24l01_tx_packet;

    typedef struct {
        uint16_t pipe;
        uint16_t data[32];
        uint16_t data_length; //TODO: NOT YET IMPLEMENTED
    } nrf24l01_rx_packet;

#define RF_RX_PACKET_BUFF_LEN 5
#define RF_TX_PACKET_BUFF_LEN 5

    typedef struct {
        return_value_t      init_return;
        volatile uint8_t    spi_rf_busy;
        volatile uint16_t   spi_rf_buffer[360];
        volatile uint16_t   spi_rf_buffer_ind[150];
        volatile uint16_t   spi_rf_buffer_rec[360];
        volatile uint16_t   spi_rf_num_msg;
        volatile uint16_t   spi_rf_cur_msg;
        volatile uint16_t   spi_rf_buffer_i;
        volatile uint8_t    RF_INTERRUPT;
        volatile uint8_t    RF_status; /*Last received status message from RF */
        volatile uint8_t    rf_data_available;

        //used in update function
        uint8_t             rf_state;
        uint16_t            rf_tx_delay;
        uint16_t            motor_nonce; //concatenation of 16 first bits of motor data

        //used to send and receive data
        uint16_t            tx_packets_start;
        uint16_t            tx_packets_end;
        nrf24l01_tx_packet  tx_packets[RF_TX_PACKET_BUFF_LEN];

        uint16_t            rx_packets_start;
        uint16_t            rx_packets_end;
        nrf24l01_rx_packet  rx_packets[RF_RX_PACKET_BUFF_LEN];
        nrf24l01_rx_packet* rx_buffer;

        //RF killswitch status
        uint8_t             rf_killswitch_state; //1 == ON, 0 == OFF
    } nrf24l01_data;

    typedef struct {
        uint16_t            frequency;
    } buzzer_data;

    typedef struct {
        int8_t  temperature;
        return_value_t state;
    } temperature_data;

    return_value_t state_init();
    
    /*
     * Resets the microcontroller and the board
     */
    void reset_board();

#ifdef	__cplusplus
}
#endif

#endif	/* POWER_STATE_H */

