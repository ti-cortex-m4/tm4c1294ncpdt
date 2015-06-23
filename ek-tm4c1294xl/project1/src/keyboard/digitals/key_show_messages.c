/*------------------------------------------------------------------------------
KEY_SHOW_MESSAGES,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../devices/devices_init.h"
#include "../key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage[]      = "Полная индикация";

static char const       *pszMessages[]   = { szMessage, "" };



void    key_SetShowMessages(void)
{
  key_SetBool(&chShowMessages, pszMessages);
}
