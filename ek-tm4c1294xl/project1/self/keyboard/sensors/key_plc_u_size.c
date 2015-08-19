/*------------------------------------------------------------------------------
KEY_PLC_U_SIZE,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../../devices/devices_init.h"
#include "../key_char_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "  Размер блока  ",
                        szMessage2[]     = "   при опросе   ",
                        szMessage3[]     = "    профилей    ",
                        szMessage4[]     = "счетчиков СЕ301 ",
                        szMessage5[]     = " по интерф. PLC ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szCharLimits, "" };



void    key_SetPlcUSize(void)
{
  key_SetCharBlocked(&chPlcUSize, pszMessages, 1, 8, boPlcUFlag, wSET_PLC_U_FLAG);
}
