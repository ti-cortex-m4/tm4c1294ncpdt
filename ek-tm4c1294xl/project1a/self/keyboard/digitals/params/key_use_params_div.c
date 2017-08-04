/*------------------------------------------------------------------------------
KEY_USE_PARAMS_DIV.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../common/key_bool.h"
#include "key_use_params_div.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "  Использовать  ",
                        szMessage2[]     = "коэффициент P104",
                        szMessage3[]     = "  для запроса   ",
                        szMessage4[]     = "    CRC52 ?     ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetUseParamsDiv(void)
{
  key_SetBool(&chUseParamsDiv, pszMessages);
}
