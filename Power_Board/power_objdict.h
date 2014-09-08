
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef POWER_OBJDICT_H
#define POWER_OBJDICT_H

#include "../libs/dspic_CanFestival/CanFestival-3/include/data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 Power_Board_valueRangeTest (UNS8 typeValue, void * value);
const indextable * Power_Board_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks);

/* Master node data struct */
extern CO_Data Power_Board_Data;
extern UNS32 Strain_Gauge1;		/* Mapped at index 0x2001, subindex 0x00*/
extern UNS32 Strain_Gauge2;		/* Mapped at index 0x2002, subindex 0x00*/
extern UNS32 Strain_Gauge3;		/* Mapped at index 0x2003, subindex 0x00*/
extern UNS32 Strain_Gauge4;		/* Mapped at index 0x2004, subindex 0x00*/
extern UNS8 Voltage_24V;		/* Mapped at index 0x4000, subindex 0x00*/

#endif // POWER_OBJDICT_H
