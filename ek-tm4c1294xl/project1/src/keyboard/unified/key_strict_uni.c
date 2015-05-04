/*------------------------------------------------------------------------------
KEY_STRICT_UNI,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../output/unified/uni.h"
#include "../key_bool.h"



//                                        0123456789ABCDEF
static char const       szMessage1[]   = "   Расширение   ",
                        szMessage2[]   = "протокола УПИО ?";

static char const       *pszMessages[] = { szMessage1, szMessage2, "" };



void    key_SetStrictUni(void)
{
  key_SetBool(&flStrictUni, pszMessages);
}
