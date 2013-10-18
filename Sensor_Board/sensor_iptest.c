#include <p33Exxxx.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "xbee_API.h"
#include "sensor_iptest.h"
#include "sensor_state.h"
#include "sensor_rf.h"
#include "sensor_led.h"
#include "sensor_pindefs.h"


bool iptest_handle_rx_packet(xbee_rx_ip_packet_t* pkt);

return_value_t iptest_init()
{
    rf_add_ip_rx_packet_handler(iptest_handle_rx_packet);
    return RET_OK;
}

void dummy_func(uint8_t stack){
        uint8_t* tmp;
        unsigned i;
    if(stack==0){
        for(i=0;i<1000;++i){
            tmp = malloc(100);
            if(tmp)
            free(tmp);
        }
    } else {
        dummy_func(stack-1);
    }
}

bool iptest_handle_rx_packet(xbee_rx_ip_packet_t* pkt)
{
    uint8_t* rf_data_;
    uint16_t rf_data_len;
    xbee_tx_ip_packet_t resp_pkt;
    //LED_1 = !LED_1;
    if(pkt==NULL){
        LED_2 = 1;
    }
    //xbee_free_packet(pkt->raw_packet);
    //return 1;
    if(pkt->options.protocol != XBEE_NET_IPPROTO_TCP || pkt->options.dest_port!=80){
        return 0;
    }
    //LED_1 = !LED_1;

    unsigned i;
    //dummy_func(3);
    //return 0;

    //rf_data_ = xbee_ip_rx_rf_data(pkt->raw_packet.raw_data); //actual packet data
    //rf_data_len = xbee_ip_rx_rf_data_len(&pkt->raw_packet);

    //send reply
    if(allocate_ip_packet(400,&resp_pkt)==RET_OK){//rf_data_len,&resp_pkt)==RET_OK){
            memcpy(resp_pkt.user_data_location,"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",400);//rf_data_,rf_data_len);
            //set options
            resp_pkt.options.dest_address[0] = pkt->options.source_addr[0];
            resp_pkt.options.dest_address[1] = pkt->options.source_addr[1];
            resp_pkt.options.dest_address[2] = pkt->options.source_addr[2];
            resp_pkt.options.dest_address[3] = pkt->options.source_addr[3];
            resp_pkt.options.dest_port = pkt->options.source_port;
            resp_pkt.options.source_port = pkt->options.dest_port;
            resp_pkt.options.leave_open = 0;
            resp_pkt.options.protocol = XBEE_NET_IPPROTO_TCP;
            //xbee_free_packet(&resp_pkt.raw_packet);
            if(transmit_ip_packet(&resp_pkt)!=RET_OK){
                //packet could not be transmitted, we need to free the memory
                xbee_free_packet(&resp_pkt.raw_packet);
//                if(resp_pkt.raw_packet.dynamic){
//                    free(resp_pkt.raw_packet.raw_data);
//                    resp_pkt.raw_packet.raw_data = 0;
//                }

            } else {
                //successfully added to the transmit buffer
            }
     } else {
         //could not allocate response packet.
     }
    //xbee_free_packet(&resp_pkt.raw_packet);

    //free the packet data
    xbee_free_packet(&pkt->raw_packet);

    return 1; //we handled this packet
}



