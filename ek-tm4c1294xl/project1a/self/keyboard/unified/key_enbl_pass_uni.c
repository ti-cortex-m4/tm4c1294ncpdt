/*------------------------------------------------------------------------------
KEY_ENBL_PASS_UNI.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../output/unified/uni.h"
#include "../common/key_bool.h"
#include "key_enbl_pass_uni.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   Пароль для   ",
                        szMessage2[]     = "протокола УПИО ?";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_SetEnblPassUni(void)
{
  key_SetBool(&chEnblPasswUni, pszMessages);
}
