/* 
 * File:   motor_uart.h
 * Author: ken
 *
 * Created on September 6, 2013, 1:54 AM
 */

#ifndef MOTOR_UART_H
#define	MOTOR_UART_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "motor_state.h"
    return_value_t uart_init();
    /*Debug functions, don't use*/
    void uart_send_byte(uint8_t data);
    void uart_send_word(uint16_t data);
    void uart_send_long(uint32_t data);
    void uart_tx_start_transmit();
    volatile uint16_t* uart_tx_cur_packet();
    void uart_tx_update_index();
    void uart_tx_compute_cks(volatile uint16_t* packet);

    volatile uint16_t* uart_rx_cur_packet();
    void uart_rx_packet_consumed();

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_UART_H */

