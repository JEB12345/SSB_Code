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

        // Provide a reference of the last modem status
	volatile uint8_t xbee_last_status;
        // The function pointer for IP callback
        void (*ip_data_func)(uint8_t *, int, s_rxinfo *);
        // The function pointer for modem status callback
	void (*modem_status_func)(uint8_t);

return_value_t confirm_checksum(wifi_data* data) {
    uint8_t sum;

    // Defined in the XBee data sheet
    sum = data->Frame_Name + data->cmdData + data->checksum;

    if(sum == XBEE_CHECKSUM_VALUE){
        return RET_OK;
    }
    else{
        return RET_ERROR;
    }
}

return_value_t xbee_spi_transmit(uint8_t* transmit_data) {
    
}
