
/* File generated by gen_cfile.py. Should not be modified. */

#include "sensor_objdict.h"

/**************************************************************************/
/* Declaration of mapped variables                                        */
/**************************************************************************/
UNS24 Strain_Gauge1 = 0x0;		/* Mapped at index 0x2001, subindex 0x00 */
UNS24 Strain_Gauge2 = 0x0;		/* Mapped at index 0x2002, subindex 0x00 */
UNS16 _24V_ADC = 0x0;		/* Mapped at index 0x3001, subindex 0x00 */

/**************************************************************************/
/* Declaration of value range types                                       */
/**************************************************************************/

#define valueRange_EMC 0x9F /* Type for index 0x1003 subindex 0x00 (only set of value 0 is possible) */
UNS32 Sensor_Board_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
    case valueRange_EMC:
      if (*(UNS8*)value != (UNS8)0) return OD_VALUE_RANGE_EXCEEDED;
      break;
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 Sensor_Board_bDeviceNodeId = 0x01;

/**************************************************************************/
/* Array of message processing information */

const UNS8 Sensor_Board_iam_a_slave = 0;

TIMER_HANDLE Sensor_Board_heartBeatTimers[1];

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    UNS32 Sensor_Board_obj1000 = 0x0;	/* 0 */
                    subindex Sensor_Board_Index1000[] = 
                     {
                       { RO, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1000 }
                     };

/* index 0x1001 :   Error Register. */
                    UNS8 Sensor_Board_obj1001 = 0x0;	/* 0 */
                    subindex Sensor_Board_Index1001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1001 }
                     };

/* index 0x1003 :   Pre-defined Error Field */
                    UNS8 Sensor_Board_highestSubIndex_obj1003 = 0; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1003[] = 
                    {
                      0x0	/* 0 */
                    };
                    ODCallback_t Sensor_Board_Index1003_callbacks[] = 
                     {
                       NULL,
                       NULL,
                     };
                    subindex Sensor_Board_Index1003[] = 
                     {
                       { RW, valueRange_EMC, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1003 },
                       { RO, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1003[0] }
                     };

/* index 0x1005 :   SYNC COB ID */
                    UNS32 Sensor_Board_obj1005 = 0x0;   /* 0 */

/* index 0x1006 :   Communication / Cycle Period */
                    UNS32 Sensor_Board_obj1006 = 0x0;   /* 0 */

/* index 0x100C :   Guard Time */ 
                    UNS16 Sensor_Board_obj100C = 0x0;   /* 0 */

/* index 0x100D :   Life Time Factor */ 
                    UNS8 Sensor_Board_obj100D = 0x0;   /* 0 */

/* index 0x1014 :   Emergency COB ID */
                    UNS32 Sensor_Board_obj1014 = 0x80 + 0x00;   /* 128 + NodeID */

/* index 0x1016 :   Consumer Heartbeat Time */
                    UNS8 Sensor_Board_highestSubIndex_obj1016 = 0;
                    UNS32 Sensor_Board_obj1016[]={0};

/* index 0x1017 :   Producer Heartbeat Time. */
                    UNS16 Sensor_Board_obj1017 = 0x64;	/* 100 */
                    ODCallback_t Sensor_Board_Index1017_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex Sensor_Board_Index1017[] = 
                     {
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1017 }
                     };

/* index 0x1018 :   Identity. */
                    UNS8 Sensor_Board_highestSubIndex_obj1018 = 4; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1018_Vendor_ID = 0x1;	/* 1 */
                    UNS32 Sensor_Board_obj1018_Product_Code = 0x0;	/* 0 */
                    UNS32 Sensor_Board_obj1018_Revision_Number = 0x0;	/* 0 */
                    UNS32 Sensor_Board_obj1018_Serial_Number = 0x0;	/* 0 */
                    subindex Sensor_Board_Index1018[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1018 },
                       { RO, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1018_Vendor_ID },
                       { RO, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1018_Product_Code },
                       { RO, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1018_Revision_Number },
                       { RO, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1018_Serial_Number }
                     };

/* index 0x1200 :   Server SDO Parameter. */
                    UNS8 Sensor_Board_highestSubIndex_obj1200 = 2; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1200_COB_ID_Client_to_Server_Receive_SDO = 0x600;	/* 1536 */
                    UNS32 Sensor_Board_obj1200_COB_ID_Server_to_Client_Transmit_SDO = 0x580;	/* 1408 */
                    subindex Sensor_Board_Index1200[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1200 },
                       { RO, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1200_COB_ID_Client_to_Server_Receive_SDO },
                       { RO, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1200_COB_ID_Server_to_Client_Transmit_SDO }
                     };

/* index 0x1400 :   Receive PDO 1 Parameter. */
                    UNS8 Sensor_Board_highestSubIndex_obj1400 = 6; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1400_COB_ID_used_by_PDO = 0x183;	/* 387 */
                    UNS8 Sensor_Board_obj1400_Transmission_Type = 0xFF;	/* 255 */
                    UNS16 Sensor_Board_obj1400_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1400_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1400_Event_Timer = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1400_SYNC_start_value = 0x0;	/* 0 */
                    subindex Sensor_Board_Index1400[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1400 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1400_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1400_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1400_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1400_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1400_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1400_SYNC_start_value }
                     };

/* index 0x1401 :   Receive PDO 2 Parameter. */
                    UNS8 Sensor_Board_highestSubIndex_obj1401 = 6; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1401_COB_ID_used_by_PDO = 0x300;	/* 768 */
                    UNS8 Sensor_Board_obj1401_Transmission_Type = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1401_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1401_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1401_Event_Timer = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1401_SYNC_start_value = 0x0;	/* 0 */
                    subindex Sensor_Board_Index1401[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1401 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1401_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1401_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1401_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1401_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1401_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1401_SYNC_start_value }
                     };

/* index 0x1402 :   Receive PDO 3 Parameter. */
                    UNS8 Sensor_Board_highestSubIndex_obj1402 = 6; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1402_COB_ID_used_by_PDO = 0x400;	/* 1024 */
                    UNS8 Sensor_Board_obj1402_Transmission_Type = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1402_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1402_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1402_Event_Timer = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1402_SYNC_start_value = 0x0;	/* 0 */
                    subindex Sensor_Board_Index1402[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1402 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1402_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1402_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1402_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1402_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1402_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1402_SYNC_start_value }
                     };

/* index 0x1403 :   Receive PDO 4 Parameter. */
                    UNS8 Sensor_Board_highestSubIndex_obj1403 = 6; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1403_COB_ID_used_by_PDO = 0x500;	/* 1280 */
                    UNS8 Sensor_Board_obj1403_Transmission_Type = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1403_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1403_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1403_Event_Timer = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1403_SYNC_start_value = 0x0;	/* 0 */
                    subindex Sensor_Board_Index1403[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1403 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1403_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1403_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1403_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1403_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1403_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1403_SYNC_start_value }
                     };

/* index 0x1600 :   Receive PDO 1 Mapping. */
                    UNS8 Sensor_Board_highestSubIndex_obj1600 = 1; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1600[] = 
                    {
                      0x30010010	/* 805371920 */
                    };
                    subindex Sensor_Board_Index1600[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1600 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1600[0] }
                     };

/* index 0x1601 :   Receive PDO 2 Mapping. */
                    UNS8 Sensor_Board_highestSubIndex_obj1601 = 8; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1601[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex Sensor_Board_Index1601[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1601 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1601[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1601[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1601[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1601[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1601[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1601[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1601[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1601[7] }
                     };

/* index 0x1602 :   Receive PDO 3 Mapping. */
                    UNS8 Sensor_Board_highestSubIndex_obj1602 = 8; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1602[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex Sensor_Board_Index1602[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1602 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1602[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1602[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1602[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1602[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1602[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1602[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1602[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1602[7] }
                     };

/* index 0x1603 :   Receive PDO 4 Mapping. */
                    UNS8 Sensor_Board_highestSubIndex_obj1603 = 8; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1603[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex Sensor_Board_Index1603[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1603 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1603[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1603[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1603[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1603[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1603[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1603[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1603[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1603[7] }
                     };

/* index 0x1800 :   Transmit PDO 1 Parameter. */
                    UNS8 Sensor_Board_highestSubIndex_obj1800 = 6; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1800_COB_ID_used_by_PDO = 0x180;	/* 384 */
                    UNS8 Sensor_Board_obj1800_Transmission_Type = 0xFF;	/* 255 */
                    UNS16 Sensor_Board_obj1800_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1800_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1800_Event_Timer = 0xA;	/* 10 */
                    UNS8 Sensor_Board_obj1800_SYNC_start_value = 0x0;	/* 0 */
                    ODCallback_t Sensor_Board_Index1800_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex Sensor_Board_Index1800[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1800 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1800_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1800_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1800_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1800_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1800_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1800_SYNC_start_value }
                     };

/* index 0x1801 :   Transmit PDO 2 Parameter. */
                    UNS8 Sensor_Board_highestSubIndex_obj1801 = 6; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1801_COB_ID_used_by_PDO = 0x280;	/* 640 */
                    UNS8 Sensor_Board_obj1801_Transmission_Type = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1801_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1801_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1801_Event_Timer = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1801_SYNC_start_value = 0x0;	/* 0 */
                    ODCallback_t Sensor_Board_Index1801_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex Sensor_Board_Index1801[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1801 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1801_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1801_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1801_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1801_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1801_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1801_SYNC_start_value }
                     };

/* index 0x1802 :   Transmit PDO 3 Parameter. */
                    UNS8 Sensor_Board_highestSubIndex_obj1802 = 6; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1802_COB_ID_used_by_PDO = 0x380;	/* 896 */
                    UNS8 Sensor_Board_obj1802_Transmission_Type = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1802_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1802_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1802_Event_Timer = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1802_SYNC_start_value = 0x0;	/* 0 */
                    ODCallback_t Sensor_Board_Index1802_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex Sensor_Board_Index1802[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1802 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1802_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1802_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1802_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1802_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1802_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1802_SYNC_start_value }
                     };

/* index 0x1803 :   Transmit PDO 4 Parameter. */
                    UNS8 Sensor_Board_highestSubIndex_obj1803 = 6; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1803_COB_ID_used_by_PDO = 0x480;	/* 1152 */
                    UNS8 Sensor_Board_obj1803_Transmission_Type = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1803_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1803_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 Sensor_Board_obj1803_Event_Timer = 0x0;	/* 0 */
                    UNS8 Sensor_Board_obj1803_SYNC_start_value = 0x0;	/* 0 */
                    ODCallback_t Sensor_Board_Index1803_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex Sensor_Board_Index1803[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1803 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1803_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1803_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1803_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1803_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&Sensor_Board_obj1803_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_obj1803_SYNC_start_value }
                     };

/* index 0x1A00 :   Transmit PDO 1 Mapping. */
                    UNS8 Sensor_Board_highestSubIndex_obj1A00 = 2; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1A00[] = 
                    {
                      0x20010018,	/* 536936472 */
                      0x20020018	/* 537002008 */
                    };
                    subindex Sensor_Board_Index1A00[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1A00 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A00[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A00[1] }
                     };

/* index 0x1A01 :   Transmit PDO 2 Mapping. */
                    UNS8 Sensor_Board_highestSubIndex_obj1A01 = 8; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1A01[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex Sensor_Board_Index1A01[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1A01 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A01[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A01[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A01[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A01[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A01[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A01[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A01[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A01[7] }
                     };

/* index 0x1A02 :   Transmit PDO 3 Mapping. */
                    UNS8 Sensor_Board_highestSubIndex_obj1A02 = 8; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1A02[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex Sensor_Board_Index1A02[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1A02 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A02[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A02[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A02[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A02[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A02[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A02[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A02[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A02[7] }
                     };

/* index 0x1A03 :   Transmit PDO 4 Mapping. */
                    UNS8 Sensor_Board_highestSubIndex_obj1A03 = 8; /* number of subindex - 1*/
                    UNS32 Sensor_Board_obj1A03[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    subindex Sensor_Board_Index1A03[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Sensor_Board_highestSubIndex_obj1A03 },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A03[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A03[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A03[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A03[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A03[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A03[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A03[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&Sensor_Board_obj1A03[7] }
                     };

/* index 0x2001 :   Mapped variable Strain_Gauge1 */
                    subindex Sensor_Board_Index2001[] = 
                     {
                       { RW, uint24, sizeof (UNS24), (void*)&Strain_Gauge1 }
                     };

/* index 0x2002 :   Mapped variable Strain_Gauge2 */
                    subindex Sensor_Board_Index2002[] = 
                     {
                       { RW, uint24, sizeof (UNS24), (void*)&Strain_Gauge2 }
                     };

/* index 0x3001 :   Mapped variable 24V_ADC */
                    subindex Sensor_Board_Index3001[] = 
                     {
                       { RW, uint16, sizeof (UNS16), (void*)&_24V_ADC }
                     };

/**************************************************************************/
/* Declaration of pointed variables                                       */
/**************************************************************************/

const indextable Sensor_Board_objdict[] = 
{
  { (subindex*)Sensor_Board_Index1000,sizeof(Sensor_Board_Index1000)/sizeof(Sensor_Board_Index1000[0]), 0x1000},
  { (subindex*)Sensor_Board_Index1001,sizeof(Sensor_Board_Index1001)/sizeof(Sensor_Board_Index1001[0]), 0x1001},
  { (subindex*)Sensor_Board_Index1017,sizeof(Sensor_Board_Index1017)/sizeof(Sensor_Board_Index1017[0]), 0x1017},
  { (subindex*)Sensor_Board_Index1018,sizeof(Sensor_Board_Index1018)/sizeof(Sensor_Board_Index1018[0]), 0x1018},
  { (subindex*)Sensor_Board_Index1200,sizeof(Sensor_Board_Index1200)/sizeof(Sensor_Board_Index1200[0]), 0x1200},
  { (subindex*)Sensor_Board_Index1400,sizeof(Sensor_Board_Index1400)/sizeof(Sensor_Board_Index1400[0]), 0x1400},
  { (subindex*)Sensor_Board_Index1401,sizeof(Sensor_Board_Index1401)/sizeof(Sensor_Board_Index1401[0]), 0x1401},
  { (subindex*)Sensor_Board_Index1402,sizeof(Sensor_Board_Index1402)/sizeof(Sensor_Board_Index1402[0]), 0x1402},
  { (subindex*)Sensor_Board_Index1403,sizeof(Sensor_Board_Index1403)/sizeof(Sensor_Board_Index1403[0]), 0x1403},
  { (subindex*)Sensor_Board_Index1600,sizeof(Sensor_Board_Index1600)/sizeof(Sensor_Board_Index1600[0]), 0x1600},
  { (subindex*)Sensor_Board_Index1601,sizeof(Sensor_Board_Index1601)/sizeof(Sensor_Board_Index1601[0]), 0x1601},
  { (subindex*)Sensor_Board_Index1602,sizeof(Sensor_Board_Index1602)/sizeof(Sensor_Board_Index1602[0]), 0x1602},
  { (subindex*)Sensor_Board_Index1603,sizeof(Sensor_Board_Index1603)/sizeof(Sensor_Board_Index1603[0]), 0x1603},
  { (subindex*)Sensor_Board_Index1800,sizeof(Sensor_Board_Index1800)/sizeof(Sensor_Board_Index1800[0]), 0x1800},
  { (subindex*)Sensor_Board_Index1801,sizeof(Sensor_Board_Index1801)/sizeof(Sensor_Board_Index1801[0]), 0x1801},
  { (subindex*)Sensor_Board_Index1802,sizeof(Sensor_Board_Index1802)/sizeof(Sensor_Board_Index1802[0]), 0x1802},
  { (subindex*)Sensor_Board_Index1803,sizeof(Sensor_Board_Index1803)/sizeof(Sensor_Board_Index1803[0]), 0x1803},
  { (subindex*)Sensor_Board_Index1A00,sizeof(Sensor_Board_Index1A00)/sizeof(Sensor_Board_Index1A00[0]), 0x1A00},
  { (subindex*)Sensor_Board_Index1A01,sizeof(Sensor_Board_Index1A01)/sizeof(Sensor_Board_Index1A01[0]), 0x1A01},
  { (subindex*)Sensor_Board_Index1A02,sizeof(Sensor_Board_Index1A02)/sizeof(Sensor_Board_Index1A02[0]), 0x1A02},
  { (subindex*)Sensor_Board_Index1A03,sizeof(Sensor_Board_Index1A03)/sizeof(Sensor_Board_Index1A03[0]), 0x1A03},
  { (subindex*)Sensor_Board_Index2001,sizeof(Sensor_Board_Index2001)/sizeof(Sensor_Board_Index2001[0]), 0x2001},
  { (subindex*)Sensor_Board_Index2002,sizeof(Sensor_Board_Index2002)/sizeof(Sensor_Board_Index2002[0]), 0x2002},
  { (subindex*)Sensor_Board_Index3001,sizeof(Sensor_Board_Index3001)/sizeof(Sensor_Board_Index3001[0]), 0x3001},
};

const indextable * Sensor_Board_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks)
{
	int i;
	*callbacks = NULL;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1017: i = 2;*callbacks = Sensor_Board_Index1017_callbacks; break;
		case 0x1018: i = 3;break;
		case 0x1200: i = 4;break;
		case 0x1400: i = 5;break;
		case 0x1401: i = 6;break;
		case 0x1402: i = 7;break;
		case 0x1403: i = 8;break;
		case 0x1600: i = 9;break;
		case 0x1601: i = 10;break;
		case 0x1602: i = 11;break;
		case 0x1603: i = 12;break;
		case 0x1800: i = 13;*callbacks = Sensor_Board_Index1800_callbacks; break;
		case 0x1801: i = 14;*callbacks = Sensor_Board_Index1801_callbacks; break;
		case 0x1802: i = 15;*callbacks = Sensor_Board_Index1802_callbacks; break;
		case 0x1803: i = 16;*callbacks = Sensor_Board_Index1803_callbacks; break;
		case 0x1A00: i = 17;break;
		case 0x1A01: i = 18;break;
		case 0x1A02: i = 19;break;
		case 0x1A03: i = 20;break;
		case 0x2001: i = 21;break;
		case 0x2002: i = 22;break;
		case 0x3001: i = 23;break;
		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &Sensor_Board_objdict[i];
}

/* 
 * To count at which received SYNC a PDO must be sent.
 * Even if no pdoTransmit are defined, at least one entry is computed
 * for compilations issues.
 */
s_PDO_status Sensor_Board_PDO_status[4] = {s_PDO_status_Initializer,s_PDO_status_Initializer,s_PDO_status_Initializer,s_PDO_status_Initializer};

const quick_index Sensor_Board_firstIndex = {
  4, /* SDO_SVR */
  0, /* SDO_CLT */
  5, /* PDO_RCV */
  9, /* PDO_RCV_MAP */
  13, /* PDO_TRS */
  17 /* PDO_TRS_MAP */
};

const quick_index Sensor_Board_lastIndex = {
  4, /* SDO_SVR */
  0, /* SDO_CLT */
  8, /* PDO_RCV */
  12, /* PDO_RCV_MAP */
  16, /* PDO_TRS */
  20 /* PDO_TRS_MAP */
};

const UNS16 Sensor_Board_ObjdictSize = sizeof(Sensor_Board_objdict)/sizeof(Sensor_Board_objdict[0]); 

CO_Data Sensor_Board_Data = CANOPEN_NODE_DATA_INITIALIZER(Sensor_Board);

