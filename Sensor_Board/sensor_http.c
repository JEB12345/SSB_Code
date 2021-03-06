#include <p33Exxxx.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../libs/dspic_http-parser/http_parser.h"
#include "../libs/dspic_jsmn/jsmn.h"
#include "superball_circularbuffer.h"
#include "xbee_API.h"
#include "sensor_http.h"
#include "sensor_state.h"
#include "sensor_rf.h"
#include "sensor_led.h"
#include "sensor_pindefs.h"
#include "sensor_memdebug.h"

http_parser* parser;
http_parser_settings* settings;
jsmn_parser* json_parser;
#define NUM_JSON_TOKENS 30
jsmntok_t json_tokens[NUM_JSON_TOKENS];
http_data http_state;
uint8_t http_rx_buffer[HTTP_RX_BUFFER_SIZE*sizeof(xbee_rx_ip_packet_t)];
char    http_header_buffer[200];
char    http_resp_buffer[1000];
extern loadcell_data loadcell_state;
extern motor_cmd_data motor_cmd_state[2];
extern  imu_data imu_state;

bool http_handle_rx_packet(xbee_rx_ip_packet_t* pkt);

return_value_t http_init()
{
    http_state.parser = malloc_dbg(sizeof(http_parser),10);
    parser = http_state.parser;
    http_parser_init(parser,HTTP_REQUEST);
    http_state.parser_settings = malloc_dbg(sizeof(http_parser_settings),11);
    settings = http_state.parser_settings;
    settings->on_body = 0;
    settings->on_header_field = 0;
    settings->on_header_value = 0;
    settings->on_headers_complete = 0;
    settings->on_message_begin = 0;
    settings->on_message_complete = 0;
    settings->on_status_complete = 0;
    settings->on_url = 0;
    http_state.num_requests = 0;
    http_state.json_parser = malloc_dbg(sizeof(jsmn_parser),44);
    json_parser = http_state.json_parser;
    if(parser == NULL || settings == NULL || json_parser == NULL){
        //could not allocate parser, error
        http_state.init_return = RET_ERROR;
    } else {
        http_state.init_return = RET_OK;
    }


    if(http_state.init_return == RET_OK){
        if(CB_Init(&http_state.rx_buffer,http_rx_buffer,HTTP_RX_BUFFER_SIZE*sizeof(xbee_rx_ip_packet_t))!=SUCCESS){
            http_state.init_return = RET_ERROR;
        } else {
            http_state.init_return = RET_OK;
        }
    }
    
    if(http_state.init_return == RET_OK){
        rf_add_ip_rx_packet_handler(http_handle_rx_packet);
    }
    return http_state.init_return;
}


int http_handle_url (http_parser *p, const char *buf, size_t len)
{
    http_state.last_url = buf;
    http_state.last_url_length = len;
    return 0;
}


int http_handle_body (http_parser *p, const char *buf, size_t len)
{
    jsmnerr_t err;
    uint8_t index;
    int j;
    unsigned i;
    char conv_buf[10];
    jsmn_init(json_parser);
    err = jsmn_parse(json_parser,buf,json_tokens,NUM_JSON_TOKENS,len);
    if(err==JSMN_SUCCESS){
        if(json_tokens[0].type == JSMN_OBJECT && json_tokens[0].size>=2){

    
            //we received a request, handle it
            index = 1;
            while(1){
                if(json_tokens[index].type==JSMN_STRING && strlen("M1BRAKE")==json_tokens[index].end-json_tokens[index].start && strncmp("M1BRAKE",&buf[json_tokens[index].start],strlen("M1BRAKE"))==0)
                {
                    //implement brake command
                    j = buf[json_tokens[index+1].start];
                    i = json_tokens[index+1].type;
                    if(json_tokens[index+1].type == JSMN_PRIMITIVE && j=='1'){
                        //brake
                        motor_cmd_state[0].brake = 1;
                    } else {
                        //disable brake
                        motor_cmd_state[0].brake = 0;
                    }
                } else if(json_tokens[index].type==JSMN_STRING && strlen("M1VEL")==json_tokens[index].end-json_tokens[index].start && strncmp("M1VEL",&buf[json_tokens[index].start],strlen("M1VEL"))==0)
                {
                    LED_3 = !LED_3; 
                    if(json_tokens[index+1].type == JSMN_PRIMITIVE){
                        //read velocity (16 bit)
                        if(json_tokens[index+1].end-json_tokens[index+1].start<=5){ //65535 max
                            for(i=0;i<json_tokens[index+1].end-json_tokens[index+1].start;++i){
                                conv_buf[i] = buf[json_tokens[index+1].start+i];
                            }
                            conv_buf[json_tokens[index+1].end] = 0; //terminate the string
                            motor_cmd_state[0].vel = strtoul(conv_buf,NULL, 16);
                        }

                    } else {
                        //invalid
                    }
                } else if(json_tokens[index].type==JSMN_STRING && strlen("M1TORQUE")==json_tokens[index].end-json_tokens[index].start && strncmp("M1TORQUE",&buf[json_tokens[index].start],strlen("M1TORQUE"))==0)
                {
                    LED_3 = !LED_3;
                    if(json_tokens[index+1].type == JSMN_PRIMITIVE){
                        //read torque (16 bit)
                        if(json_tokens[index+1].end-json_tokens[index+1].start<=5){ //65535 max
                            for(i=0;i<json_tokens[index+1].end-json_tokens[index+1].start;++i){
                                conv_buf[i] = buf[json_tokens[index+1].start+i];
                            }
                            conv_buf[json_tokens[index+1].end] = 0; //terminate the string
                            motor_cmd_state[0].torque = strtoul(conv_buf,NULL, 16);
                        }

                    } else {
                        //invalid
                    }
                }
                index += 2;
                if(index>json_tokens[0].size-1){
                    break;
                }
            }
        }
    }
    return 0;
}

void http_process()
{
    xbee_rx_ip_packet_t rx_pkt;
    uint8_t* rf_data_p;
    uint16_t rf_data_len;
    if(http_state.init_return!=RET_OK){
        return;//not running
    }

    //check if top packet in circular buffer is a TCP packet on port 80
    if(CB_ReadMany(&http_state.rx_buffer,&rx_pkt,sizeof(xbee_rx_ip_packet_t))!=SUCCESS){
        return;//empty buffer
    } 

    //we have a packet to handle, handle it now!
    rf_data_p = xbee_ip_rx_rf_data(rx_pkt.raw_packet.raw_data); //actual packet data
    rf_data_len = xbee_ip_rx_rf_data_len(&rx_pkt.raw_packet);
    //parse the packet
    http_parser_init(parser,HTTP_REQUEST);
    http_state.last_url_length = 0;
    http_state.last_url = 0;
    settings->on_url = http_handle_url;
    settings->on_body = http_handle_body;

    http_parser_execute(parser,settings,rf_data_p,(size_t)rf_data_len);

        
    //check if we found a url
    if(http_state.last_url!=0 && http_state.last_url_length>0){//    && rf_data_len>3 && rf_data_p[0]=='G' && rf_data_p[1]=='E'&&rf_data_p[2]=='T'){
        http_state.num_requests++;
        led_rgb_set(50,0,255);
        http_state.last_url[http_state.last_url_length]=0;

        //prepare response
        char* resp =
        "{\"result\": {\"message\":\"req. %lu\",\"url\":\"%s\",\"acc\":[%d,%d,%d]}, \"error\": null, \"id\": 1}\r\n"
        "\r\n";
        sprintf(http_resp_buffer,resp,http_state.num_requests,http_state.last_url,(imu_state.acc_read_data[0]<<8)|imu_state.acc_read_data[1],(imu_state.acc_read_data[2]<<8)|imu_state.acc_read_data[3],(imu_state.acc_read_data[4]<<8)|imu_state.acc_read_data[5]);

        char* header = "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %u\r\n"
        "\r\n";//application/json-rpc\r\n"

        sprintf(http_header_buffer,header,strlen(http_resp_buffer));


        

        xbee_tx_ip_packet_t resp_pkt;
        //allocate memory for response
        if(allocate_ip_packet(strlen(http_resp_buffer)+strlen(http_header_buffer),&resp_pkt)==RET_OK){
            memcpy(resp_pkt.user_data_location,http_header_buffer,strlen(http_header_buffer));
            memcpy(resp_pkt.user_data_location+strlen(http_header_buffer),http_resp_buffer,strlen(http_resp_buffer));
            //set options
            resp_pkt.options.dest_address[0] = rx_pkt.options.source_addr[0];
            resp_pkt.options.dest_address[1] = rx_pkt.options.source_addr[1];
            resp_pkt.options.dest_address[2] = rx_pkt.options.source_addr[2];
            resp_pkt.options.dest_address[3] = rx_pkt.options.source_addr[3];
            resp_pkt.options.dest_port = rx_pkt.options.source_port;
            resp_pkt.options.source_port = rx_pkt.options.dest_port;
            resp_pkt.options.leave_open = 0;
            resp_pkt.options.protocol = XBEE_NET_IPPROTO_TCP;
            //xbee_free_packet(&resp_pkt.raw_packet);
            if(transmit_ip_packet(&resp_pkt)!=RET_OK){
                //packet could not be transmitted, we need to free the memory
                xbee_free_packet(&resp_pkt.raw_packet);
            } 
        } else {
            //could not allocate response packet.
        }
        
    }
    //free the packet data
    xbee_free_packet(&rx_pkt.raw_packet);
}

bool http_handle_rx_packet(xbee_rx_ip_packet_t* pkt)
{
    if(pkt->options.protocol != XBEE_NET_IPPROTO_TCP){// || pkt->options.dest_port!=HTTP_PORT){
        return 0;
    }
    //add to circular buffer
    if(CB_WriteMany(&http_state.rx_buffer,pkt,sizeof(xbee_rx_ip_packet_t),1)!=SUCCESS){
        //buffer is full, free the packet (it's lost)

        return 0;
    } else {
        //packet was added to the http processing queue

    }
    return 1; //we handled this packet
}


