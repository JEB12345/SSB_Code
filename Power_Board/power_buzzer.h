/* 
 * File:   power_buzzer.h
 * Author: ken
 *
 * Created on January 15, 2015, 5:32 PM
 */

#ifndef POWER_BUZZER_H
#define	POWER_BUZZER_H
#include "power_pindef.h"
#include "power_state.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define TONE_C_1	33	//Hz
#define TONE_Cs_1	35	//Hz
#define TONE_D_1	37	//Hz
#define TONE_Ds_1	39	//Hz
#define TONE_E_1	41	//Hz
#define TONE_F_1	44	//Hz
#define TONE_Fs_1	46	//Hz
#define TONE_G_1	49	//Hz
#define TONE_Gs_1	52	//Hz
#define TONE_A_1	55	//Hz
#define TONE_As_1	58	//Hz
#define TONE_B_1	62	//Hz
#define TONE_C_2	65	//Hz
#define TONE_Cs_2	69	//Hz
#define TONE_D_2	73	//Hz
#define TONE_Ds_2	78	//Hz
#define TONE_E_2	82	//Hz
#define TONE_F_2	87	//Hz
#define TONE_Fs_2	92	//Hz
#define TONE_G_2	98	//Hz
#define TONE_Gs_2	104	//Hz
#define TONE_A_2	110	//Hz
#define TONE_As_2	117	//Hz
#define TONE_B_2	123	//Hz
#define TONE_C_3	131	//Hz
#define TONE_Cs_3	139	//Hz
#define TONE_D_3	147	//Hz
#define TONE_Ds_3	156	//Hz
#define TONE_E_3	165	//Hz
#define TONE_F_3	175	//Hz
#define TONE_Fs_3	185	//Hz
#define TONE_G_3	196	//Hz
#define TONE_Gs_3	208	//Hz
#define TONE_A_3	220	//Hz
#define TONE_As_3	233	//Hz
#define TONE_B_3	247	//Hz
#define TONE_C_4	262	//Hz
#define TONE_Cs_4	277	//Hz
#define TONE_D_4	294	//Hz
#define TONE_Ds_4	311	//Hz
#define TONE_E_4	330	//Hz
#define TONE_F_4	349	//Hz
#define TONE_Fs_4	370	//Hz
#define TONE_G_4	392	//Hz
#define TONE_Gs_4	415	//Hz
#define TONE_A_4	440	//Hz
#define TONE_As_4	466	//Hz
#define TONE_B_4	494	//Hz
#define TONE_C_5	523	//Hz
#define TONE_Cs_5	554	//Hz
#define TONE_D_5	587	//Hz
#define TONE_Ds_5	622	//Hz
#define TONE_E_5	659	//Hz
#define TONE_F_5	698	//Hz
#define TONE_Fs_5	740	//Hz
#define TONE_G_5	784	//Hz
#define TONE_Gs_5	831	//Hz
#define TONE_A_5	880	//Hz
#define TONE_As_5	932	//Hz
#define TONE_B_5	988	//Hz
#define TONE_C_6	1047	//Hz
#define TONE_Cs_6	1109	//Hz
#define TONE_D_6	1175	//Hz
#define TONE_Ds_6	1245	//Hz
#define TONE_E_6	1319	//Hz
#define TONE_F_6	1397	//Hz
#define TONE_Fs_6	1480	//Hz
#define TONE_G_6	1568	//Hz
#define TONE_Gs_6	1661	//Hz
#define TONE_A_6	1760	//Hz
#define TONE_As_6	1865	//Hz
#define TONE_B_6	1976	//Hz
#define TONE_C_7	2093	//Hz
#define TONE_Cs_7	2217	//Hz
#define TONE_D_7	2349	//Hz
#define TONE_Ds_7	2489	//Hz
#define TONE_E_7	2637	//Hz
#define TONE_F_7	2794	//Hz
#define TONE_Fs_7	2960	//Hz
#define TONE_G_7	3136	//Hz
#define TONE_Gs_7	3322	//Hz
#define TONE_A_7	3520	//Hz
#define TONE_As_7	3729	//Hz
#define TONE_B_7	3951	//Hz
#define TONE_C_8	4186	//Hz
#define TONE_Cs_8	4435	//Hz
#define TONE_D_8	4699	//Hz
#define TONE_Ds_8	4978	//Hz
#define TONE_E_8	5274	//Hz
#define TONE_F_8	5588	//Hz
#define TONE_Fs_8	5920	//Hz
#define TONE_G_8	6272	//Hz
#define TONE_Gs_8	6645	//Hz
#define TONE_A_8	7040	//Hz
#define TONE_As_8	7459	//Hz
#define TONE_B_8	7902	//Hz
#define TONE_C_9	8372	//Hz
#define TONE_Cs_9	8870	//Hz
#define TONE_D_9	9397	//Hz
#define TONE_Ds_9	9956	//Hz
#define TONE_E_9	10548	//Hz
#define TONE_F_9	11175	//Hz
#define TONE_Fs_9	11840	//Hz
#define TONE_G_9	12544	//Hz
#define TONE_Gs_9	13290	//Hz
#define TONE_A_9	14080	//Hz
#define TONE_As_9	14917	//Hz
#define TONE_B_9	15804	//Hz

/*
 #compute frequencies
 for o_idx,o in enumerate(octaves):
    for l_idx,l in enumerate(letters):
        print "#define TONE_%s_%d\t%d\t//Hz"%(l,o,round(440*2**((l_idx+o_idx*12-45)/12.)))
 */

return_value_t buzzer_init();

return_value_t buzzer_set_frequency(uint16_t freq);

void buzzer_update(); //call periodically


#ifdef	__cplusplus
}
#endif

#endif	/* POWER_BUZZER_H */

