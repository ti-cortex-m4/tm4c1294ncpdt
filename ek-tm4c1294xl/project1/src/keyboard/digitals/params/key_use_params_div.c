/*------------------------------------------------------------------------------
KEY_USE_PARAMS_DIV.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../key_bool.h"



//                                           0123456789ABCDEF
static char const       szUseParamsDiv1[] = "  Использовать  ",
                        szUseParamsDiv2[] = "коэффициент P104",
                        szUseParamsDiv3[] = "  для запроса   ",
                        szUseParamsDiv4[] = "    CRC52 ?     ";

static char const       *pszUseParamsDiv[] = { szUseParamsDiv1, szUseParamsDiv2, szUseParamsDiv3, szUseParamsDiv4, "" };



void    key_SetUseParamsDiv(void)
{
  key_SetBool(&flUseParamsDiv, pszUseParamsDiv);
}
