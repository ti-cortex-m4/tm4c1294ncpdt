/*------------------------------------------------------------------------------
KEY_ENBL_WDT,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_program.h"
#include "../settings.h"
#include "key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "¬ключенный WDT ?";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetEnblWDT(void)
{
  key_SetBool(&chEnblWDT, pszMessages);
}
