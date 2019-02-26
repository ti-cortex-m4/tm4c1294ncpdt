/*------------------------------------------------------------------------------
KEY_TIME_ZONE34.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_char.h"
#include "key_time_zone34.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Часовой пояс ESM";

static char const       *pszMessages[]  = { szMessage, szNumberLimits, "" };



void    key_SetTimeZone34(void)
{
  key_SetChar(&chTimeZone34, pszMessages, 0, 13);
}
