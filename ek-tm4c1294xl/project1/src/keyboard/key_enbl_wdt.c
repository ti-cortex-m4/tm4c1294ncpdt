/*------------------------------------------------------------------------------
KEY_ENBL_KEYS,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/digitals.h"
#include "../key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "¬ключенный WDT ?";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetEnblWDT(void)
{
  key_SetBool(&chEnblWDT, pszMessages);
}
