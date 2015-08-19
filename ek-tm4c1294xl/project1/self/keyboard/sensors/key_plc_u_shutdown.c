/*------------------------------------------------------------------------------
KEY_PLC_U_SHUTDOWN,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../devices/devices_init.h"
#include "../common/key_int_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "Число неактивных",
                        szMessage2[]     = "   получасов    ",
                        szMessage3[]     = "   при опросе   ",
                        szMessage4[]     = " профилей СЕ301 ",
                        szMessage5[]     = " по интерф. PLC ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szNumberLimits, "" };



void    key_SetPlcUShutdown(void)
{
  key_SetIntBlocked(&chPlcUShutdown, pszMessages, 10, 500, boPlcUFlag, wSET_PLC_U_FLAG);
}
