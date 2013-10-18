/* 
 * File:   sensor_memdebug.h
 * Author: ken
 *
 * Created on October 17, 2013, 11:26 AM
 */

#ifndef SENSOR_MEMDEBUG_H
#define	SENSOR_MEMDEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stddef.h>
#include <stdint.h>

#define MEMDBG_GUARDSIZE    8
#define MEMDBG_SIZE         4000
#define MEMDBG_POOLSIZE     25

    typedef struct mem_element{
        uint16_t offset;
        uint16_t size;
        uint8_t  freed;
        struct mem_element* prev;
        struct mem_element* next;
        uint8_t*    mem_ptr;
        uint8_t tag;
        uint16_t mem_pool_idx;
    } mem_element;

void memtest();

void init_memory();

void* malloc_dbg(size_t size, uint8_t tag);

void free_dbg(void* ptr, uint8_t tag);

int memcheck();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_MEMDEBUG_H */

