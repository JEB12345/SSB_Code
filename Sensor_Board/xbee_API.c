/*
 * File:   xbee_API.c
 * Author: jonathan
 *
 * Created on October 1, 2013, 8:37 PM
 */

#include "xbee_API.h"
#include "sensor_state.h"
#include "sensor_pindefs.h"
#include "sensor_rf.h"

return_value_t confirm_checksum(wifi_data* data) {
    uint8_t sum;

    // Defined in the XBee data sheet
    sum = data.Frame_Name + data.cmdData + data.checksum;

    if(sum == checksum_value){
        return RET_OK;
    }
    else{
        return RET_ERROR;
    }
}

return_value_t xbee_spi_transmit(uint8_t* transmit_data) {
    
}
