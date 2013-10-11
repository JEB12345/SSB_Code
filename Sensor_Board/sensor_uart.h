/* 
 * File:   sensor_uart.h
 * Author: ken
 *
 * Created on October 8, 2013, 5:55 PM
 */

#ifndef SENSOR_UART_H
#define	SENSOR_UART_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>

#include "sensor_state.h"

    return_value_t uart_init();

    void uart_tx_start_transmit();
    volatile uint8_t* uart_tx_cur_packet();
    void uart_tx_update_index();
    void uart_tx_compute_cks(volatile uint8_t* packet);

    volatile uint8_t* uart_rx_cur_packet();
    void uart_rx_packet_consumed();



#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_UART_H */

