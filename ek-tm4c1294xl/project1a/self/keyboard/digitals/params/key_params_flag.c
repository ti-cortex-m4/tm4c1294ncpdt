/*------------------------------------------------------------------------------
KEY_PARAMS_FLAG.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../common/key_bool.h"
#include "key_params_flag.h"



//                                          0123456789ABCDEF
static char const       szMessage[]      = "Параметры ?     ";

static char const       *pszMessages[]   = { szMessage, "" };



void    key_SetParamsFlag(void)
{
  key_SetBool(&chParamsFlag, pszMessages);
}
