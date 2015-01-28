#include "power_buzzer.h"
#include "p33Exxxx.h"
#include "power_state.h"
#include "power_pindef.h"

extern timer_data timer_state;
buzzer_data buzzer_state;

return_value_t buzzer_init() {
    BUZZER = 0;

    T4CONbits.TON = 0;

    //configure OC4 module
    OC4CON1 = 0b0;
    OC4CON2 = 0b0;

    OC4CON1bits.OCTSEL = 0b10; //clock = TIMER 4
    OC4CON2bits.SYNCSEL = 0b01110; //timer 4 sync
    //OC4TMR = 1000;
    //OC4R = 1000;
    OC4CON1bits.OCM = 3; //toggle mode


    buzzer_state.frequency = 0;
    return RET_OK;
}

return_value_t buzzer_set_frequency(uint16_t freq) { //in Hz
    uint32_t tmr_temp;
    if (freq < 70) { //if freq < 70, we cannot find a valid (16bit) timer setting
        T4CONbits.TON = 0;
        TMR4 = 0x0;

        buzzer_state.frequency = 0;
    } else if(freq!=buzzer_state.frequency){
        //freq = 70000000/(8*PR4)/2
        //PR4 = 70000000/(8xfreq)
        //PR4 = 8750000/freq/2
        //PR4 = 4375000/freq
        tmr_temp = 4375000;
        tmr_temp /= freq;

        T4CONbits.TON = 0;
        TMR4 = 0x00; //Clear Timer 4 register
        PR4 = (uint16_t) (tmr_temp & 0xFFFF); //Fp / (TCKPS*PR4) = LoopTime => 70000000/(8*PR4)=100000Hz
        OC4R = PR4;
        OC4TMR = 0;
        T4CONbits.TON = 1;
        buzzer_state.frequency = freq;
    }
    return RET_OK;
}

void buzzer_update() {
    if (EN_BACKUP_5V5 && EN_VBAT_5V5) {
        //error: both power sources active
        //Fast beep
        if (timer_state.systime % 200 == 0) {
//            LED_R = !LED_R;
        }
        if (timer_state.systime % 500 == 0) {
            buzzer_set_frequency(TONE_A_6);
        } else if (timer_state.systime % 500 == 250) {
            buzzer_set_frequency(0);
        }
    } else if (EN_BACKUP_5V5) {
        //Slow beep when the main battery goes down
        if (timer_state.systime % 3000 == 0) {
            buzzer_set_frequency(TONE_A_5);
//            LED_R = 0;
        } else if (timer_state.systime % 3000 == 150) {
            buzzer_set_frequency(0);
//            LED_R = 1;
        }
    } else {
//        LED_R = 1;
    }
}

