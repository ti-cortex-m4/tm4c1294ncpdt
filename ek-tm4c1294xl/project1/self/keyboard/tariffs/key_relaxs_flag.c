/*------------------------------------------------------------------------------
KEY_RELAXS_FLAG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../tariffs/relaxs.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Праздники ?     ";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetRelaxsFlag(void)
{
  key_SetBool(&chRelaxsFlag, pszMessages);
}
