#include "clock.h"
#include "p33Exxxx.h"

_FOSCSEL(FNOSC_FRC & IESO_OFF & PWMLOCK_OFF); //PWMLOCK_OFF needed to configure PWM on MC variant
//_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE);
_FWDT(FWDTEN_OFF);
/* Disable JTAG */
_FICD(JTAGEN_OFF & ICS_PGD2);

clock_data clock_state;

return_value_t clock_init()
{
    /*
     * 70 MIPS:
     * FOSC = Fin*(PLLDIV+2)/((PLLPRE+2)*2(PLLPOST+1))
     * FOSC = 7.37MHz(74+2)/((0+2)*2(0+1)) = 140.03Mhz
     * Fcy = FOSC/2
     */

    PLLFBD = 74;
    CLKDIVbits.PLLPRE = 0;
    CLKDIVbits.PLLPOST = 0;

    // Initiate Clock Switch to FRC oscillator with PLL (NOSC=0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(OSCCON | 0x01);

    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b001);

    while (OSCCONbits.LOCK!= 1);
    clock_state.fcy = 70000000;
    clock_state.init_return = RET_OK;
    return clock_state.init_return;
}
