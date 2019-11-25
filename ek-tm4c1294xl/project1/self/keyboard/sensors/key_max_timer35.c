/*------------------------------------------------------------------------------
KEY_MAX_TIMER35.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_char.h"
#include "key_max_timer35.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Часовой пояс ESM";

static char const       *pszMessages[]  = { szMessage, szNumberLimits, "" };



void    key_SetMaxTimer35(void)
{
  key_SetChar(&chTimer34, pszMessages, 0, 13);
}
