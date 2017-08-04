/*------------------------------------------------------------------------------
KEY_LOGICAL,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../settings.h"
#include "common/key_char.h"



//                                          0123456789ABCDEF
static char const       szMessage[]      = "Логический номер";

static char const       *pszMessages[]   = { szMessage, szNumberLimits, "" };



void    key_SetLogical(void)
{
  key_SetChar(&chLogical, pszMessages, 0, 255);
}
