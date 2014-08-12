/* 
 * File:   main.c
 * Author: ken
 *
 * Created on May 12, 2014, 3:18 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#pragma config FOSC=INTOSC, PLLEN=OFF, WDTE=ON, MCLRE=ON,
#pragma config CLKOUTEN=OFF,CP=OFF,BOREN=ON
#pragma config WRT=OFF,STVREN=ON,BORV=LO,LVP=ON

#define _XTAL_FREQ  500000

#define OUTPUT LATA2
#define INPUT_0 RA5
#define INPUT_1 RA4

#define INPUT_0_TIMEOUT 50
#define INPUT_1_TIMEOUT 1000
#define INPUT_OK_DURATION 2000

#define S_DISABLED 0
#define S_ENABLED 1
/*
 * 
 */
int main(int argc, char** argv) {
    unsigned long last_trans_0, last_trans_1;
    unsigned prev_input_0, prev_input_1;
    unsigned long disabled_ctr;
    unsigned state,prev_state;
    TRISA2 = 0; //output
    TRISA4 = 1; //uC inputs
    TRISA5 = 1;
    ANSELA = 0;
    //enable pull ups on input pins
    nWPUEN = 0;
    WPUA4 = 1;
    WPUA5 = 1;
    //default = disable output
    OUTPUT = 0;
//    //Test buzzer : 7.1KHz
//        while(1){
//            OUTPUT = OUTPUT^1;
//            __nop();
//            __nop();
//            __nop();
//            __nop();
//            __nop();
//            __nop();
//            __nop();
//            __nop();
//            __nop();
//            //for(state=0;state<1;++state);
//            asm("CLRWDT");
//        }
    //boot timeout
    __delay_ms(200);
    __delay_ms(200);
    __delay_ms(100);

    //reset transition counters
    last_trans_0 = 0;
    last_trans_1 = 0;
    //previous state
    prev_input_0 = INPUT_0;
    prev_input_1 = INPUT_1;

    disabled_ctr = 0;

    state = prev_state = S_DISABLED;
    while (1) {
        asm("CLRWDT"); //default timeout = 2s
        __delay_ms(1); //check input every ms

        //transition?
        if (prev_input_0 == INPUT_0) {
            ++last_trans_0;
        } else {
            last_trans_0 = 0;
        }
        if (prev_input_1 == INPUT_1) {
            ++last_trans_1;
        } else {
            last_trans_1 = 0;
        }
        prev_input_0 = INPUT_0;
        prev_input_1 = INPUT_1;

        OUTPUT = 1;

//        switch (state) {
//            case S_DISABLED:
//                OUTPUT = 0;
//
//                if(last_trans_0>=INPUT_0_TIMEOUT || last_trans_1>=INPUT_1_TIMEOUT){
//                    disabled_ctr = 0;
//                } else {
//                    ++disabled_ctr;
//                }
//                if(disabled_ctr>INPUT_OK_DURATION){
//                    state = S_ENABLED;
//                }
//                break;
//            case S_ENABLED:
//                OUTPUT = 1;
//                //if no transitions detected for a while: switch to S_DISABLED
//                if(last_trans_0>=INPUT_0_TIMEOUT || last_trans_1>=INPUT_1_TIMEOUT){
//                    state = S_DISABLED;
//                }
//                break;
//        };
        if(state!=prev_state){
            last_trans_0 = last_trans_1 = 0;
            disabled_ctr = 0;
        }
        prev_state = state;
    }
    asm("RESET");
}

