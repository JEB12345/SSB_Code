#include "power_state.h"
#include "power_clock.h"
#include "p33Exxxx.h"

#ifdef TRANSMITTER 
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF & PWMLOCK_OFF); //PWMLOCK_OFF needed to configure PWM
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);
_FWDT(FWDTEN_OFF);
/* Disable JTAG */
_FICD(JTAGEN_OFF & ICS_PGD1);
#endif

#ifdef NO_BOOTLOADER
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF & PWMLOCK_OFF); //PWMLOCK_OFF needed to configure PWM
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);
_FWDT(FWDTEN_OFF);
/* Disable JTAG */
_FICD(JTAGEN_OFF & ICS_PGD1);
#endif

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
    while (OSCCONbits.LOCK!= 1);
    clock_state.fcy = 70000000;
    clock_state.init_return = RET_OK;
    return clock_state.init_return;
}
