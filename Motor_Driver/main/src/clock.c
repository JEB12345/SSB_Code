#include "../include/config.h"
#include PICINCLUDE
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE);
_FWDT(FWDTEN_OFF);
/* Disable JTAG */
_FICD(JTAGEN_OFF & ICS_PGD2);

void clock_init(){
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
}