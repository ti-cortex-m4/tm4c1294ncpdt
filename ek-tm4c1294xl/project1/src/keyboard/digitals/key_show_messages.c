/*------------------------------------------------------------------------------
KEY_SHOW_MESSAGES.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../devices/devices_init.h"
#include "../key_flag.h"



//                                          0123456789ABCDEF
static char const       szShowMessages[] = "Полная индикация";

static char const       *pszShowMessages[] = { szShowMessages, "" };



void    key_SetShowMessages(void)
{
  key_SetBool(&flShowMessages, pszShowMessages);
}
