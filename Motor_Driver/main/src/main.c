/* 
 * File:   main.c
 * Author: ken
 *
 * Created on August 14, 2013, 3:41 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"
#include PICINCLUDE
#include "../include/clock.h"
#include "../include/pindefs.h"
#include "../include/util.h"

/*
 * 
 */
int main() {
    clock_init();
    pin_init();
    
    LED1_ON;
    while(1){
    delay_ms(200);
    LED1_TOGGLE;
    LED2_TOGGLE;
    LED3_TOGGLE;
    LED4_TOGGLE;
    }

}

