/*------------------------------------------------------------------------------
KEY_HIDE_MESSAGES,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../devices/devices_init.h"
#include "../key_bool.h"



//                                           0123456789ABCDEF
static char const       szMessage1[]      = "Ускоренный вывод",
                        szMessage2[]      = "  на индикацию  ";

static char const       *pszMessages[]    = { szMessage1, szMessage2, "" };



void    key_SetHideMessages(void)
{
  key_SetBool(&chHideMessages, pszMessages);
}
