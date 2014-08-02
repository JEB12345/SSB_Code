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
    unsigned int volatile   systime;        //updated by a timer
    unsigned int            prev_systime;   //updated in main loop
} timer_data;

// ADC data Struct for buffer
typedef struct {
    uint16_t                AN6;
    uint16_t                AN7;
    uint16_t                AN8;
    uint16_t                AN11;
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
    } system_data;

    return_value_t state_init();
    
    /*
     * Resets the microcontroller and the board
     */
    void reset_board();

#ifdef	__cplusplus
}
#endif

#endif	/* POWER_STATE_H */

