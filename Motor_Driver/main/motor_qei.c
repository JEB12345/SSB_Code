#include "p33Exxxx.h"
#include "motor_qei.h"
#include "motor_state.h"
#include "motor_led.h"

qei_data qei_state;
    return_value_t qei_init()
    {
        qei_state.init_return = RET_OK;
        QEI1CONbits.INTDIV = 0b100; //divide FCY by 16 for pulse duration
        QEI1CONbits.CCM = 0b00;//encoder mode
        QEI1CONbits.CNTPOL = 0b0;//Counter direction is positive unless modified by external Up/Down signal
        QEI1CONbits.GATEN = 0b0; //disable external count gate enable pin
        QEI1CONbits.IMV = 0b10; //no idea...
        QEI1CONbits.PIMOD = 0b000; //index pulse does not reset the position counter

        QEI1IOCbits.QCAPEN = 0;
        QEI1IOCbits.FLTREN = 0; //filter disabled for now
        QEI1IOCbits.SWPAB = 0; //do we need to swap A & B???

        QEI1IOCbits.QEAPOL = 0;
        QEI1IOCbits.QEAPOL = 0;

        POS1HLD = 0x0;
        POS1CNTL = 0x0;

        INDX1HLD = 0x1FFF;
        INDX1CNTL = 0xFFFF;

        QEI1CONbits.QEIEN = 1; //activate encoder
        return qei_state.init_return;
    }

    void qei_update()
    {
        qei_state.rotor_position = POS1CNTL; //always read low word first
        qei_state.rotor_position |= ((uint32_t)POS1HLD)<<16;
        uint32_t old_index = qei_state.index;
        qei_state.index = INDX1CNTL; //always read low word first
        qei_state.index |= ((uint32_t)INDX1HLD)<<16;
        if(qei_state.index>old_index){
            led_intensity_set(255,0,0,0);

        }else if (qei_state.index<old_index){
            led_intensity_set(0,0,0,255);
        }
    }