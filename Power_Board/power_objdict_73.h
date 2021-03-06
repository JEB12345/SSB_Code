
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef POWER_OBJDICT_73_H
#define POWER_OBJDICT_73_H

#include "../libs/dspic_CanFestival/CanFestival-3/include/data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 Power_Board_valueRangeTest (UNS8 typeValue, void * value);
const indextable * Power_Board_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks);

/* Master node data struct */
extern CO_Data Power_Board_Data;
extern UNS32 power73_adc_state_mV_5V5_out;		/* Mapped at index 0x2030, subindex 0x01 */
extern UNS32 power73_adc_state_mA_5V5_out;		/* Mapped at index 0x2030, subindex 0x02 */
extern UNS32 power73_adc_state_mW_5V5_out;		/* Mapped at index 0x2030, subindex 0x03 */
extern UNS32 power73_adc_state_mV_main_battery;		/* Mapped at index 0x2030, subindex 0x04 */
extern UNS32 power73_adc_state_mV_vbackup_battery;		/* Mapped at index 0x2030, subindex 0x05 */
extern INTEGER32 power73_adc_state_mA_motor_current;		/* Mapped at index 0x2030, subindex 0x06 */
extern UNS32 power73_adc_state_mV_motor_voltage;		/* Mapped at index 0x2030, subindex 0x07 */
extern INTEGER32 power73_adc_state_mW_motor_power;		/* Mapped at index 0x2030, subindex 0x08 */
extern INTEGER8 power73_adc_state_C_temp;		/* Mapped at index 0x2030, subindex 0x09 */
extern UNS8 power73_power_switches_24_killswitch;		/* Mapped at index 0x2031, subindex 0x01 */
extern UNS8 power73_power_switches_5V5_Out_1;		/* Mapped at index 0x2031, subindex 0x02 */
extern UNS8 power73_power_switches_5V5_Out_2;		/* Mapped at index 0x2031, subindex 0x03 */
extern UNS8 power73_power_switches_5V5_Out_3;		/* Mapped at index 0x2031, subindex 0x04 */
extern UNS8 power73_power_switches_5V5_Out_4;		/* Mapped at index 0x2031, subindex 0x05 */
extern UNS32 power73_nrf_time;		/* Mapped at index 0x2032, subindex 0x00*/

#endif // POWER_OBJDICT_73_H
