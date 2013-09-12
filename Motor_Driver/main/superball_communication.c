#include "p33Exxxx.h"
#include <stdlib.h>

#include "superball_circularbuffer.h"
#include "superball_communication.h"

//superball_buffer superball_receive_buffer;
superball_buffer superball_transmit_buffers[16];
//uint8_t superball_receive_data[SUPERBALL_RECEIVE_DATA_SIZE];
uint8_t superball_transmit_data[SUPERBALL_NUM_TRANSMIT_IF*SUPERBALL_TRANSMIT_DATA_SIZE]; //buffer 0 is the dropped packets queue, the other correspond to their IF index
superball_route superball_routing_table;

int superball_communication_init()
{
    int ret = SUCCESS;
    unsigned i;
    //ret = CB_Init(&superball_receive_buffer,superball_receive_data,SUPERBALL_RECEIVE_DATA_SIZE);
    for(i=0; i<SUPERBALL_NUM_TRANSMIT_IF;++i){
        if(CB_Init(&(superball_transmit_buffers[i]),superball_transmit_data+SUPERBALL_TRANSMIT_DATA_SIZE*i,SUPERBALL_TRANSMIT_DATA_SIZE)!=SUCCESS){
            ret = STANDARD_ERROR;
        }
    }

    superball_routing_table.next = &superball_routing_table;
    superball_routing_table.previous = &superball_routing_table;
    
    if(superball_routes_setup()!=SUCCESS){
        ret = STANDARD_ERROR;
    }

    return ret;
}

int superball_routes_setup()
{
    superball_route* tmp;
    superball_route* to_wifi;
    
    superball_route* drop_all;

    to_wifi = malloc(sizeof(superball_route));
    tmp = to_wifi;
    if(!tmp){
        return STANDARD_ERROR;
    } else {
        superball_routing_table.next = tmp;
        superball_routing_table.previous = tmp;
        tmp->previous = &superball_routing_table;
        tmp->next = &superball_routing_table;
        tmp->interface_out = IF_UDP;
        tmp->destination_type = ADDR_SINGLE;
        tmp->destination = 0;
        tmp->interface_in = IF_ANY;
        tmp->origin = 0;
        tmp->origin_type = ADDR_ANY; //any interface and any address, to a destination 0 goes out over UDP
    }

    drop_all = malloc(sizeof(superball_route));
    tmp = drop_all;
    if(!tmp){
        return STANDARD_ERROR;
    } else {
        to_wifi->next = tmp;
        superball_routing_table.previous = tmp;
        tmp->previous = to_wifi;
        tmp->next = &superball_routing_table;
        tmp->interface_out = IF_DROP;
        tmp->destination_type = ADDR_ANY;
        tmp->destination = 0;
        tmp->interface_in = IF_ANY;
        tmp->origin = 0;
        tmp->origin_type = ADDR_ANY; //any interface and any address to any destination, will be dropped if not matched
    }

    return SUCCESS;
}

void superball_packet_init(superball_packet* packet)
{
    packet->TTL = 15;
    packet->data = 0;
    packet->destination = 0;
    packet->interface_in = IF_UNKNOWN;
    packet->interface_out = IF_UNKNOWN;
    packet->length = 0;
    packet->origin = 0;
    packet->options = 0;
}

/**
 * Frees the data of the given packet, not the packet (metadata) itself (which can be e.g. on the stack)
 * @param packet
 */
void superball_free_packet(superball_packet* packet)
{
    if(packet->data)
        free(packet->data);
}

/*
 Note: the packet will be (deep)copied into a buffer, so the caller needs/can to free the packet pointer if necessary.
 * packet data has to be dynamic memory (will be freed on transmission)
 */
int superball_route_packet(superball_packet* packet)
{
    superball_route* route = &superball_routing_table;
    uint8_t match;
    unsigned i;
    if(packet->TTL--==0){
        //drop packet
        superball_free_packet(packet);
    } else {
        //we need to compute the interface_out, based on interface_in, origin and destination
        //iterate the routing table
        while(route->next!=&superball_routing_table){
            route = route->next;
            match = 1;
            //does origin match?
            if(match && !route->origin_type==ADDR_ANY){
                //SINGLE OR MULTIPLE are considered to mean 'unique'
                match = route->origin == packet->origin;
            }
            //does destination match?
            if(match && !route->destination_type==ADDR_ANY){
                //SINGLE OR MULTIPLE are considered to mean 'unique'
                match = route->destination == packet->origin;
            }
            //does input interface match?
            if(match && !route->interface_in!=IF_ANY){
                match = route->interface_in == packet->interface_in;
            }
            
            if(match){
                //send to correct buffer
                packet->interface_out = route->interface_out;
                switch(packet->interface_out){
                    case IF_UART1:
                    case IF_UART2:
                    case IF_SPI1:
                    case IF_SPI2:
                    case IF_I2C1:
                    case IF_I2C2:
                    case IF_CAN:
                    case IF_UDP:
                    case IF_TCP:
                    case IF_LOCAL:
                        //copy to specific buffer
                        CB_WriteMany(&superball_transmit_buffers[packet->interface_out], packet, sizeof(superball_packet),1);
                        break;
                    case IF_ALL:
                        //copy to all buffers except drop buffer
                        for(i=IF_UART1; i<=IF_LOCAL;++i){
                            CB_WriteMany(&superball_transmit_buffers[i], packet, sizeof(superball_packet),1);
                        }
                        break;
                    case IF_UNKNOWN:
                    case IF_INVALID:
                    case IF_ANY:
                    case IF_DROP:
                    default:
                        //drop the packet: copy to buffer 0
                        CB_WriteMany(&superball_transmit_buffers[0], packet, sizeof(superball_packet),1);
                        break;
                };

                if(!route->destination_type==ADDR_MULTIPLE){
                    break;//only apply first matching rule, unless ADDR_MULTIPLE is indicated
                }
            }
        }
    }

}

/**
 * Copies a packet from buffer to the given packet pointer.
 * returns SUCCESS if a packet was found else STANDARD_ERROR
 */
int superball_next_transmit_packet(superball_interface_t interface, superball_packet* packet)
{
    return CB_ReadMany(&superball_transmit_buffers[interface],&packet,sizeof(packet));
}
