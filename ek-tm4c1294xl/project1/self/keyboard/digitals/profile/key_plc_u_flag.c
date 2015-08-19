/*------------------------------------------------------------------------------
KEY_PLC_U_FLAG,C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../devices/devices_init.h"
#include "../../key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " Интерфейс PLC  ",
                        szMessage2[]     = " для счетчиков  ",
                        szMessage3[]     = "    CE301 ?     ";

static char const       *pszMessages[] = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetPlcUFlag(void)
{
  key_SetBool(&chPlcUFlag, pszMessages);
}
