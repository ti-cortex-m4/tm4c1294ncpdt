/*------------------------------------------------------------------------------
KEY_FIX_PARAMS_BUGS.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../common/key_bool.h"
#include "key_fix_params_bugs.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   Исправлять   ",
                        szMessage2[]     = "   ошибки при   ",
                        szMessage3[]     = "     чтении     ",
                        szMessage4[]     = "  параметров ?  ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetFixParamsBugs(void)
{
  key_SetBool(&chFixParamsBugs, pszMessages);
}
