/*------------------------------------------------------------------------------
KEY_SEPARATE_CAN.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../devices/devices.h"
#include        "../key_flag.h"



//                                         0123456789ABCDEF
static char const       szSeparateCan[] = "Раздельный опрос";

static char const       *pszSeparateCan[] = { szSeparateCan, "" };



void    key_SetSeparateCan(void)
{
  key_SetFlag(&flSeparateCan, pszSeparateCan);
}
