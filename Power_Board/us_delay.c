/* 
 * File:   us_delay.c
 * Author: jonathan
 *
 * Created on October 10, 2014, 1:31 PM
 */

#include "us_delay.h"

//void Delay_us(unsigned int delay)
//void Delay_us(uint32_t delay)
inline void Delay_us(unsigned int delay)
{
    uint16_t i;
    for (i = 0; i < delay; i++){
        __asm__ volatile ("repeat #69");
        __asm__ volatile ("nop");
    }
}
