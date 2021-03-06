/* 
 * File:   sensor_state.h
 * Author: ken
 *
 * Created on August 28, 2013, 11:55 PM
 */

#ifndef SENSOR_STATE_H
#define	SENSOR_STATE_H
#include <stdint.h>
#include "superball_circularbuffer.h"

#define bool uint8_t

    typedef enum
        {
            RET_OK = 0,
            RET_ERROR = 1,
            RET_UNKNOWN = 127
        }
    return_value_t;

    typedef enum {
         SPI_IDLE            =0,
         SPI_LED_ON          =1,
         SPI_LED_OFF         =2,
         SPI_ME_READ_ANGLE   =3,
         SPI_ME_READ_ANGLE_2 =4,
         SPI_LED_END         =5,
         SPI_VARIOUS         =6,  //useful during initialization
         SPI_SG_READ_DATA_1  =7,
         SPI_SG_READ_DATA_2  =8,
         SPI_SG_READ_DATA_3  =9,
         SPI_SG_READ_DATA_4  =10,
         SPI_SG_READ_DATA_END =11
    } spi_sg_state_t;

    //#define LC_CIRCULAR_BUFFER_SIZE 3


    /*
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
    } DMA_SPI_LC_state_t;*/

    typedef enum {
        XBEE_STATE_INIT,
        XBEE_STATE_IDLE_TRANSMIT_IP,
        XBEE_STATE_IDLE_TRANSMIT_AT,
        XBEE_STATE_RECEIVE_HEADER,
        XBEE_STATE_RECEIVE_FRAME,
        XBEE_STATE_PACKET_RECEIVED,
        XBEE_STATE_TRANSMIT,
        XBEE_STATE_TRANSMITTED
    } xbee_state_t;

//    enum I2C_STATES {
//    IDLE,
//    GYRO_WAIT_START,
//
//    WAIT_START_READ_STATE, //beginning of transaction to read the
//    ADDRESS_READ_STATE,
//    REGISTER_ADDRESS_READ_STATE,
//    RS_READ_STATE,
//    REGISTER_ADDRESS_READ_READ_STATE,
//    BYTE_READ_READ_STATE,
//    STOP_READ_STATE,
//    NEXT_BYTE_READ_STATE,
//
//    WAIT_START_WRITE_STATE,
//    ADDRESS_WRITE_STATE,
//    BYTE_WRITE_STATE,
//    STOP_WRITE_STATE,
//    WAIT_START_SCAN_STATE,
//    ADDRESS_SCAN_STATE
//
//};

    //maintain all state variables here
//    typedef struct {
//        return_value_t          init_return;
//        volatile enum I2C_STATES i2c_state;
//        volatile enum I2C_STATES i2c_err;
//        volatile uint8_t acc_read_register;
//        volatile uint8_t acc_read_num;
//        volatile uint8_t acc_read_data[25];
//        //volatile uint8 acc_read_done;
//        volatile uint8_t i2c_address, i2c_address_2;
//        volatile uint16_t acc_cnt, i2c_err_5, i2c_err_2, i2c_err_sum;
//        volatile uint8_t acc_write_num;
//        volatile uint8_t acc_write_data[20];
//        volatile uint8_t acc_write_register;
//        volatile uint8_t acc_write_done;
//        volatile uint8_t i2c_dev[128];
//        volatile uint8_t scan_address;
//        int volatile            state;
//    } imu_data;
    
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
    } can_data;

    typedef struct {
        return_value_t          init_return;
        //sets the color of the RGB led
        uint8_t                 rgb_red;
        uint8_t                 rgb_green;
        uint8_t                 rgb_blue;
    } led_data;

    /*typedef struct DMA_SPI_LC_read_value{
    unsigned char DATA[3];
    unsigned char STATUS;
} DMA_SPI_LC_read_value;*/


    typedef struct {
        return_value_t          init_return;
        uint32_t volatile       values[8]; // Number of ADC Channels is 8 in pseudo mode
        uint8_t volatile           data_ready; //data available was signalled by ADC
        volatile uint16_t spi_state;
        volatile uint16_t sg_data_0, sg_data_1, sg_data_2, sg_data_3; //received data (SPI)
        volatile uint16_t sg_status;
        uint32_t volatile       num_measurements[8]; //counts the number of measurements received per channel
        volatile bool error;
    } loadcell_data;

    // This structure is used with the IP data callback to
// report information about the incoming IP data
typedef struct {
    uint8_t             frame_id;
    uint8_t             source_addr[4];		// Address from which the data originated
    uint16_t            source_port;		// Port from which the data originated
    uint16_t            dest_port;		// Port on which the data arrived. If 0xBEE, data was received using app service
    uint8_t             protocol;		// XBEE_NET_IPPROTO_UDP / TCP
    uint16_t            sequence;		// Segment number
    uint16_t            total_packet_length;	// Total length of the incoming packet
    uint16_t            current_offset;	// Current offset within the incoming packet of this segment
    bool                final;			// True for the final segment of this packet
    bool                checksum_error;		// Checksum indication flag
} s_rxinfo;

// Note that due to buffer size restrictions, an incoming data packet (of up to 1400 bytes length)
// will be delivered in multiple calls to the ip data reception callback
// The sequence number will be the same for all calls for a given packet and then incremented
// for the next packet
// A checksum error will only be flagged (true) on the last given call for a packet / sequence


// This structure is used to provide transmission options when transmiting IP data
typedef struct {
    uint8_t             frame_id;
    uint8_t             dest_address[4];
    uint16_t            dest_port;
    uint16_t            source_port;
    uint8_t             protocol;		// XBEE_NET_IPPROTO_UDP / TCP
    bool                leave_open;
} s_txoptions;

typedef struct {
    uint16_t            at_cmd_id;
    uint8_t             frame_id;
} s_atoptions;

#define XBEE_RESPONSE_CB bool (*at_cmd)(uint8_t, uint16_t, uint8_t, uint8_t*, uint16_t,bool) //frame_id, at_cmd, status, raw packet data, length, dynamic (needs to be freed), return true to indicate that the AT cmd was handled
#define XBEE_TRANSMITTED_CB void (*ip_tx)()

typedef union {
    XBEE_TRANSMITTED_CB;
    XBEE_RESPONSE_CB;
} response_callback_t;

    typedef struct {
        uint8_t*        raw_data;
        uint16_t        length;
        bool            dynamic;
        bool            valid;
        void (*transmitted)();
        response_callback_t response_received; //void (*response_received)();
        uint16_t        response_time_out; //response_time_out>0 indicates that there is a valid callback!!!
    } xbee_packet_t;

    typedef struct {
        xbee_packet_t   raw_packet;
        uint8_t*        user_data_location;
        uint16_t        allocationLength;
        s_txoptions     options;
    } xbee_tx_ip_packet_t;

    typedef struct {
        xbee_packet_t   raw_packet;
        s_rxinfo        options;
    } xbee_rx_ip_packet_t;

    typedef struct {
        xbee_packet_t   raw_packet;
        s_atoptions     options;
    } xbee_at_packet_t;

    typedef enum { INIT_IN_PROCESS = 0,  INIT_SUCCESS = 1, INIT_ERROR = 127} network_status_t;

    typedef struct {
        return_value_t          init_return;
        return_value_t          init_SPI2_return;
        return_value_t          init_XBEE_return;
        uint32_t                dma2_int_cnt;
        uint32_t                dma3_int_cnt;
        int                     state;
        xbee_state_t            xbee_state;
        bool                    xbee_at_req;
        CircularBuffer          ip_tx_buffer;
        CircularBuffer          ip_rx_buffer;
        CircularBuffer          raw_rx_buffer;
        xbee_tx_ip_packet_t     cur_tx_ip_packet;
        xbee_at_packet_t        at_packet;
        bool                    process_lock; //lock to indicate that the state is changing (prevent interrupts from updating)
        xbee_at_packet_t        cur_tx_at_packet;
        xbee_packet_t*          cur_raw_packet;
        xbee_packet_t           cur_rx_raw_packet;
        unsigned                cur_tx_packet_type;
        uint16_t                cur_packet_timeout_ctr;
        xbee_packet_t           pending_rx_packet;
        uint8_t                 cur_modem_status;
        network_status_t        cur_network_status;
        bool (*ip_rx_pkt_handlers[10])(xbee_rx_ip_packet_t*);
        unsigned                num_ip_rx_pkt_handlers;
        bool                    attn_detected;
        bool                    receive_header_int;
        uint16_t                nATTN_timeout;
    } rf_data;

    typedef struct {
        bool                    callback_success;
        uint8_t                 cur_state;
        uint8_t                 error_count;
        bool                 connection_pending;
    }network_data;

    typedef struct {
        return_value_t          init_return;
        unsigned int volatile   systime;        //updated by a timer
        unsigned int            prev_systime;   //updated in main loop
    } timer_data;

    typedef enum {STATE_UNKNOWN = 0, STATE_INITIALIZED = 1, STATE_ERROR = 127} state_t;
    typedef struct {
        return_value_t          init_return;
        state_t volatile state; //system state
    } system_data;

    typedef struct {
        return_value_t          init_return;
        uint32_t                fcy;
    } clock_data;

    /*typedef struct {
        return_value_t          init_return;
        uint8_t                 cur_state;
        uint8_t                 prev_state;
        uint16_t volatile       last_update_tmr;
        unsigned volatile       direction; //0 not moving, 1 positive, 2 negative
    } hallsensor_data;*/
    /*
    typedef struct {
        return_value_t          init_return;
        uint16_t volatile       rotor_position;
        uint16_t volatile       rotor_turns;
        float volatile          rotor_state;
        float volatile          rotor_state_interpolated;
        float volatile          rotor_speed; //in sectors/s (60deg/s)
        float                   wire_length;
    } motor_data;
    */
    return_value_t state_init();
    
    /*
     * Resets the microcontroller and the board
     */
    void reset_board();

    #define UART_TX_PACKET_MAX_LEN  50
#define UART_TX_PACKET_BUFF_LEN 50
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
        void*                   parser;
        void*                   parser_settings;
        void*                   json_parser;
        CircularBuffer          rx_buffer;
        char*                   last_url;
        uint16_t                last_url_length;
        uint32_t                num_requests;
    } http_data;

    typedef struct {
        bool                    brake;
        bool                    coast;
        uint16_t                vel;
        uint16_t                torque;
        uint32_t                position;
        uint16_t                p,i,d;
        uint8_t                 mode;
        bool                    dir;
        bool                    decay_mode;
        int32_t                 cur_pos;
        int16_t                 cur_vel;
    } motor_cmd_data;

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_STATE_H */

