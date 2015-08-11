/*------------------------------------------------------------------------------
KEY_PARAMS_FLAG,C

 Флаг разрешения опроса мгновенных параметров
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Параметры ?     ";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetParamsFlag(void)
{
  key_SetBool(&chParamsFlag, pszMessages);
}
