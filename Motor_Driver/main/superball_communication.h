/* 
 * File:   superball_communication.h
 * Author: ken
 *
 * Created on September 11, 2013, 9:14 PM
 */

#ifndef SUPERBALL_COMMUNICATION_H
#define	SUPERBALL_COMMUNICATION_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "superball_circularbuffer.h"

#define SUPERBALLPACKET_URGENT  0b00000001
#define SUPERBALL_RECEIVE_DATA_SIZE    sizeof(superball_packet)*20
#define SUPERBALL_TRANSMIT_DATA_SIZE    sizeof(superball_packet)*5
#define SUPERBALL_NUM_TRANSMIT_IF       16
#define SUPERBALLPACKET_IS_URGENT(_X)   (SUPERBALLPACKET_URGENT&(_X))

    #define superball_buffer CircularBuffer
    
    typedef enum {
        IF_UNKNOWN = 0,
        IF_INVALID = 1,
        IF_ANY = 2,
        IF_DROP = 3,
        IF_UART1 = 4,
        IF_UART2 = 5,
        IF_SPI1 = 6,
        IF_SPI2 = 7,
        IF_I2C1 = 8,
        IF_I2C2 = 9,
        IF_CAN = 10,
        IF_UDP = 11,
        IF_TCP = 12,
        IF_LOCAL = 14,
        IF_ALL = 255,
    } superball_interface_t;

    typedef enum {
        ADDR_ANY = 0,
        ADDR_SINGLE = 1,
        ADDR_MULTIPLE = 2
    } superball_address_t;

    typedef struct {//__attribute__((__packed__)) {
        unsigned        options;//:8;
        unsigned        origin;//:10;
        unsigned        destination;//:10;
        unsigned        TTL;//:4;
        unsigned        length;//:8;
    } superball_packet_header;

    typedef struct {
        superball_packet_header       header;
        uint8_t*                      data;//order is important for efficient serialization
        superball_interface_t         interface_in:8;
        superball_interface_t         interface_out:8;        
    } superball_packet;

    typedef struct superball_route superball_route;
    struct superball_route {
        superball_interface_t interface_in:8;
        superball_interface_t interface_out:8;
        unsigned        origin:10;
        unsigned        destination:10;
        superball_address_t origin_type:4;
        superball_address_t destination_type:4;
        void*   data;
        superball_route* next;
        superball_route* previous;
    };
    int superball_communication_init();
    void superball_packet_init(superball_packet* packet);
    int superball_route_packet(superball_packet* packet);
    int superball_next_transmit_packet(superball_interface_t interface, superball_packet* packet);
    int superball_packet_serialize(const superball_packet* packet, uint8_t* serialized);
    int superball_packet_deserialize(const volatile uint8_t* serialized, superball_packet* packet);
    uint16_t superball_packet_length(const superball_packet* packet);
    //private
    int superball_routes_setup();


#ifdef	__cplusplus
}
#endif

#endif	/* SUPERBALL_COMMUNICATION_H */

