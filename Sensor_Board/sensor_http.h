/* 
 * File:   sensor_http.h
 * Author: ken
 *
 * Created on October 14, 2013, 3:32 PM
 */

#ifndef SENSOR_HTTP_H
#define	SENSOR_HTTP_H
#include "sensor_state.h"
#ifdef	__cplusplus
extern "C" {
#endif

#define HTTP_PORT   80
#define HTTP_RX_BUFFER_SIZE 10

    /**
     * @brief http_init Initalizes the structs to handle
     * the http messages sent out by the Sensor Board
     *
     * The user will call this function to setup the http structs. Each message has a standard format based on the json style.
     *
     * @return The fuction returns an error only if the parser, setup, or json
     * did not initalize correctly.
     */
    return_value_t http_init();

    /**
     * @brief http_process Checks the circular buffer for a xbee packet then processes it
     *
     * @return Nothing.
     */
    void http_process();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_HTTP_H */

