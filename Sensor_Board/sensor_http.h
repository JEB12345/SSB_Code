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

    return_value_t http_init();
    void http_process();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_HTTP_H */

