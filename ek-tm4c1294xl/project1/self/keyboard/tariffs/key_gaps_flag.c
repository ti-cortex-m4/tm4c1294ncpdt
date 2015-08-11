/*------------------------------------------------------------------------------
KEY_GAPS_FLAG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../tariffs/gaps.h"
#include "../key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Тарифные периоды";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetGapsFlag(void)
{
  key_SetBool(&chGapsFlag, pszMessages);
}
