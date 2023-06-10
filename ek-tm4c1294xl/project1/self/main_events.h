/*------------------------------------------------------------------------------
MAIN_EVENTS!H


------------------------------------------------------------------------------*/

#include "main_basic.h"



// тип 'код события'
typedef enum
{
//  EVE_PREVNEXTTIME       = 0,
  EVE_POSTNEXTTIME       = 1,
  EVE_WATCHDOG           = 2,
  EVE_START              = 3,
  EVE_RESTART            = 4,
  EVE_PASSWORD           = 5,
  EVE_DOOROPEN           = 6,
  EVE_DOORCLOSE          = 7,
  EVE_CONTACTS1          = 8,
  EVE_CONTACTS2          = 9,
  EVE_CONTACTSMODE       = 10,
  EVE_CONTACTS3_0_ON     = 11,
  EVE_CONTACTS3_0_OFF    = 12,
//  EVE_CONTACTS3_1_ON     = 13,
//  EVE_CONTACTS3_1_OFF    = 14,
  EVE_MANUAL3_0_ON       = 15,
  EVE_MANUAL3_0_OFF      = 16,
  EVE_MANUAL3_1_ON       = 17,
  EVE_MANUAL3_1_OFF      = 18,
  EVE_VALUE3_UP          = 19,
  EVE_VALUE3_DOWN        = 20,
  EVE_VALUE3_COUNTER     = 21,
  EVE_CONTACTS3_COUNTER  = 22,
  EVE_CONTACTS3_START    = 23,
  EVE_OPENCALC1          = 24,
  EVE_OPENCALC2          = 25,
  EVE_PREVNEXTTIME2      = 26,

  EVE_EVENTS_BADLINK     = 32,
  EVE_EVENTS_BADDATA     = 33,
  EVE_EVENTS_OMISSION    = 34,
  EVE_EVENTS_A           = 35,
  EVE_EVENTS_B           = 36,

  EVE_EDIT_DIGITAL1      = 40,
  EVE_EDIT_DIGITAL2      = 41,
  EVE_EDIT_KEY10         = 42,
  EVE_EDIT_KEY11         = 43,
  EVE_EDIT_KEY20         = 44,
  EVE_EDIT_KEY21         = 45,
  EVE_EDIT_ADDRESS10     = 46,
  EVE_EDIT_ADDRESS11     = 47,
  EVE_EDIT_ADDRESS20     = 48,
  EVE_EDIT_ADDRESS21     = 49,

  EVE_CANAL_DISABLED     = 62,
  EVE_PROFILE_DISABLED   = 63,
  EVE_PROFILEOPEN        = 64,
  EVE_SPECIALOPEN        = 65,
//  EVE_PROFILE            = 66,
//  EVE_DIGITAL            = 67,
//  EVE_EXTENDED           = 68,
//  EVE_ESC_V_OK           = 69,
//  EVE_ESC_V_ERROR        = 70,
//  EVE_ESC_V_DATA         = 71,
//  EVE_ESC_S_OK           = 72,
//  EVE_ESC_S_ERROR        = 73,
//  EVE_ESC_S_DATA         = 74,
//  EVE_ESC_U_OK           = 75,
//  EVE_ESC_U_ERROR        = 76,
//  EVE_ESC_U_DATA         = 77,
  EVE_DIGITAL_OK         = 78,
//  EVE_PROFILE_OK         = 79,
//  EVE_PROFILE_ERROR      = 80,
  EVE_MODEMCONNECT1      = 81,
  EVE_MODEMCONNECT2      = 82,
  EVE_MODEMBREAK1        = 83,
  EVE_MODEMBREAK2        = 84,
//  EVE_PROFILECLOSE       = 85,
  EVE_DIGITALCLOSE       = 86,
  EVE_SPECIALCLOSE       = 87,
  EVE_RECALC10           = 88,
  EVE_RECALC11           = 89,
  EVE_RECALCFREE         = 90,
  EVE_RECALC20           = 91,
  EVE_RECALC21           = 92,
  EVE_PROFILE_ERROR2     = 93,
  EVE_PROFILECLOSE2      = 94,
  EVE_REFILL1            = 95,
  EVE_REFILL2            = 96,
  EVE_PROFILE_OK2        = 97,
  EVE_PREVIOUS_TOP       = 98,
  EVE_PROFILE2           = 99,
  EVE_CURRENT2_CANALS    = 109,
  EVE_CURRENT2_VALUE     = 110,
  EVE_CURRENT2_LIMIT     = 111,
  EVE_CURRENT2_OVERFLOW  = 112,
  EVE_DEVICE_P_DEFECT    = 113,
  EVE_EXTENDED_0_ERROR   = 114,

  EVE_PROFILE_INTERVAL_STOP     = 115,
  EVE_PROFILE_INTERVAL_BREAK    = 116,
  EVE_PROFILE_INTERVAL_START    = 117,

  EVE_MODEM_PROFILEOPEN  = 126,
  EVE_MODEM_SPECIALOPEN  = 127,
  EVE_MODEM_PROFILE      = 128,
  EVE_MODEM_ERROR        = 129,
  EVE_MODEMBAUD          = 130,
  EVE_MODEMBAUD_OK       = 131,
  EVE_MODEMBAUD_NEXT     = 132,
  EVE_MODEMCOMMON1       = 133,
  EVE_MODEMCOMMON1_OK    = 134,
  EVE_MODEMCOMMON1_NEXT  = 135,
  EVE_MODEMESCAPE1_NEXT  = 136,
  EVE_MODEMHOOKOFF1      = 137,
  EVE_MODEMHOOKOFF1_NEXT = 138,
  EVE_MODEMCOMMON2       = 139,
  EVE_MODEMCOMMON2_NEXT  = 140,
  EVE_MODEMCUSTOM        = 141,
  EVE_MODEMCUSTOM_OK     = 142,
  EVE_MODEMCUSTOM_NEXT   = 143,
  EVE_MODEMCONNECT       = 144,
  EVE_MODEMCONNECT_OK    = 145,
  EVE_MODEMCONNECT_NEXT  = 146,
  EVE_MODEM_KEYBREAK     = 147,
  EVE_MODEM_PROFILEOK    = 148,
//  EVE_MODEM_PROFILEERROR = 149,
  EVE_MODEM_PROFILEDONE1 = 150,
  EVE_MODEM_PROFILEDONE2 = 151,
  EVE_MODEMESCAPE2       = 152,
  EVE_MODEMESCAPE2_OK    = 153,
  EVE_MODEMHOOKOFF2_NEXT = 154,
  EVE_MODEMHOOKOFF2_OK   = 155,
  EVE_MODEMESCAPE3_NEXT  = 156,
  EVE_MODEMHOOKOFF3      = 157,
  EVE_MODEMHOOKOFF3_OK   = 158,
  EVE_MODEMHOOKOFF3_NEXT = 159,
  EVE_MODEMDTROFF        = 160,
  EVE_MODEM_PROFILEERROR2= 161,

  EVE_GPS_MANUAL         = 192,
  EVE_GPS_AUTO           = 193,
  EVE_GPS_BADLINK        = 194,
  EVE_GPS_GOODLINK       = 195,
  EVE_GPS_BADGPS         = 196,
  EVE_GPS_GOODGPS_1      = 197,
  EVE_GPS_BADFORMAT      = 198,
  EVE_GPS_BADDATE        = 199,
  EVE_GPS_BADTIME        = 200,
  EVE_GPS_OK             = 201,

  EVE_PROGRAM_2          = 210,
  EVE_EXT_CORRECT2       = 211,
  EVE_ESC_K              = 212,
  EVE_ESC_k              = 213,
  EVE_INQ_CORRECT1       = 214,
  EVE_INQ_CORRECT2       = 215,
  EVE_INQ_CORRECT4       = 209, // 216
  EVE_TIME_OK            = 217,
  EVE_GPS_GOODGPS_2      = 218,
  EVE_UNI_CORRECT        = 219,

  EVE_SMK_MANUAL         = 220,
  EVE_SMK_AUTO           = 221,
  EVE_SMK_BADLINK        = 222,
  EVE_SMK_GOODLINK       = 223,
  EVE_SMK_BADSMK         = 224,
  EVE_SMK_GOODSMK_1      = 225,
  EVE_SMK_BADFORMAT      = 226,
  EVE_SMK_BADDATE        = 227,
  EVE_SMK_BADTIME        = 228,
  EVE_SMK_OK             = 229,

  EVE_CHECKUP_START      = 230,
  EVE_CHECKUP_NEXT       = 231,
  EVE_CHECKUP_VALUE      = 232,
  EVE_CHECKUP_DAY        = 233,
  EVE_CHECKUP_MON        = 234,
  EVE_CHECKUP_CANAL      = 235,
  EVE_CHECKUP_DAY_SKIP   = 236,
  EVE_CHECKUP_MON_SKIP   = 237,
  EVE_CHECKUP_DAY_NEXT   = 238,
  EVE_CHECKUP_MON_NEXT   = 239,
  EVE_CHECKUP_DAY_FAIL   = 240,
  EVE_CHECKUP_MON_FAIL   = 241,
  EVE_CHECKUP_INFO       = 242,

  EVE_PH2_START          = 100,
  EVE_PH2_FINISH         = 101,
  EVE_PH2_DEBUG          = 102,
} event;


// тип 'событие'
typedef struct
{
  time          ti;
  ulong         cdwRecord;
  event         ev;
  uchar         mpbBuff[8];
} record;


// тип 'класс событий'
typedef enum
{
  CLA_KEYBOARD          = 0,
  CLA_SYSTEM            = 1,
  CLA_DIGITAL           = 2,
  CLA_IMPULSE           = 3,
  CLA_MODEM             = 4,
  CLA_PHONES2           = 5
} class;


// тип 'класс событий'
typedef enum
{
  CLA_AUXILIARY         = 0,
} class2;
