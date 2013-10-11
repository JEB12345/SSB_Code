
#include "sensor_uart.h"
#include "sensor_state.h"
#include "p33Exxxx.h"
#include <stdint.h>

uart_data uart_state;


return_value_t uart_init()
{
    uart_state.init_return = RET_OK;
    /*TX*/
    U1MODEbits.UEN = 0b00;
    U1STAbits.UTXEN = 1;
    U1STAbits.UTXISEL0 = 0;
    U1STAbits.UTXISEL1 = 0;
    uart_state.tx_idle = 1;
    U1MODEbits.BRGH = 1;
    U1BRG = 34; //500000 baud/s
    IEC0bits.U1TXIE = 1;
    IFS0bits.U1TXIF = 0;
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1; //DO THIS AFTER UARTEN OR IT WON'T WORK!!!
    uart_state.tx_packets_start = 0;
    uart_state.tx_packets_end = 0;
    uart_state.bytes_sent = 0;
    uart_state.tx_num_errors = 0;
    uart_state.packets_sent = 0;

    /*RX*/
    IEC0bits.U1RXIE = 1;        //enable receive interrupt
    U1STAbits.URXISEL = 00;     //Interrupt flag bit is set when a character is received
    uart_state.rx_num_errors = 0;
    uart_state.rx_packets_start = 0;
    uart_state.rx_packets_end = 0;
    uart_state.bytes_received = 0;
    uart_state.rx_state = UART_RX_STATE_INIT;
    uart_state.rx_buffer = uart_state.rx_packets[0];
    uart_state.rx_buffer_len = 0;
    uart_state.packets_received = 0;
     

     return uart_state.init_return;
}


inline volatile uint8_t* uart_tx_cur_packet()
{
    return uart_state.tx_packets[uart_state.tx_packets_end];
}

void uart_tx_compute_cks(volatile uint8_t* packet)
{
    uint8_t uart_tx_cks = 0;
    unsigned i;
    for(i=1;i<packet[2]+1;++i){
        uart_tx_cks ^= packet[i];
    }
    packet[packet[2]+1] = uart_tx_cks;
}

inline void uart_tx_update_index()
{
    if (uart_state.tx_packets_end >= UART_TX_PACKET_BUFF_LEN - 1)
        uart_state.tx_packets_end = 0;
    else
        ++uart_state.tx_packets_end;
}

volatile uint8_t* uart_rx_cur_packet()
{
    if(uart_state.rx_packets_start != uart_state.rx_packets_end) {
        //handle a single packet
        return uart_state.rx_packets[uart_state.rx_packets_start];
    } else {
        return 0;
    }
}

void uart_rx_packet_consumed()
{
    if (uart_state.rx_packets_start >= UART_RX_PACKET_BUFF_LEN - 1)
        uart_state.rx_packets_start = 0;
    else
        ++uart_state.rx_packets_start;
}

void __attribute__((__interrupt__ , no_auto_psv)) _U1ErrInterrupt(void) {
    uart_state.tx_packets_start = 0;
    uart_state.tx_packets_end = 0;

    IFS0bits.U1TXIF = 0;
    U1STAbits.OERR = 0;
    uart_state.tx_idle = 1;
    uart_state.tx_num_errors++;
}

void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    if(uart_state.tx_packets_start!=uart_state.tx_packets_end){
        //a packet needs to be sent or is in transmission
       
        U1TXREG = uart_state.tx_packets[uart_state.tx_packets_start][uart_state.tx_buffer_idx++];
        uart_state.bytes_sent++;
        if(uart_state.tx_buffer_idx==uart_state.tx_packets[uart_state.tx_packets_start][2]+2){
            uart_state.tx_buffer_idx = 0;
            ++uart_state.tx_packets_start;
            ++uart_state.packets_sent;
            if(uart_state.tx_packets_start>=UART_TX_PACKET_BUFF_LEN)
                uart_state.tx_packets_start = 0;
        }
    } else {
        uart_state.tx_idle = 1;
    }

    IFS0bits.U1TXIF = 0;
}

void uart_tx_start_transmit()
{
    uart_state.tx_idle = 0;
    _U1TXInterrupt();
}

void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    uint16_t tmp = U1RXREG&0xFF; //read byte
    //TODO: reset state after timeout
    switch (uart_state.rx_state){
        case UART_RX_STATE_INIT:
            if(tmp==0xFF){
                uart_state.rx_state = UART_RX_STATE_CMD;
                //don't store start byte
            }// else {
                //do nothing
            //}
            break;
        case UART_RX_STATE_CMD:
            //store cmd
            uart_state.rx_buffer[uart_state.rx_buffer_len++] = uart_state.rx_cks = tmp;
            uart_state.rx_state = UART_RX_STATE_LEN;
            break;
        case UART_RX_STATE_LEN:
            //store len
            uart_state.rx_buffer[uart_state.rx_buffer_len++] = tmp;
            uart_state.rx_len = tmp;
            //len is total packet len from CMD up to (exclusive) checksum
            uart_state.rx_cks ^= tmp; //update checksum
            // e.g. 0XFF CMD LEN DATA1 DATA2 DATA3 CKS : LEN = 5
            if(uart_state.rx_len!=0){// && uart_state.rx_len==17){
                uart_state.rx_state = UART_RX_STATE_DATA;
            } else {
                uart_state.rx_state = UART_RX_STATE_CKS;
            }
            break;
        case UART_RX_STATE_DATA:
            uart_state.rx_buffer[uart_state.rx_buffer_len++] = tmp;
            uart_state.rx_cks ^= tmp; //update checksum
            if(uart_state.rx_buffer_len>=uart_state.rx_len){
                uart_state.rx_state = UART_RX_STATE_CKS;
            }
            break;
        case UART_RX_STATE_CKS:
            //checksum == XOR(CMD,LEN,DATA1,...,DATAN)
            if(tmp==uart_state.rx_cks){


                    //Something else (legacy mode) received)
                    //update circular buffer
                    if(uart_state.rx_packets_end==UART_RX_PACKET_BUFF_LEN-1)
                        uart_state.rx_packets_end = 0;
                    else
                        ++uart_state.rx_packets_end;

                    uart_state.rx_buffer = uart_state.rx_packets[uart_state.rx_packets_end];
                    ++uart_state.packets_received;
                    //indicate that new packet is valid and go to next buffer location

            } //else == invalid
            else {
                ++uart_state.rx_num_errors;
            }
            uart_state.rx_state = UART_RX_STATE_INIT;
            uart_state.rx_buffer_len = 0; //reset buffer
            break;
    };
    IFS0bits.U1RXIF = 0;
}


