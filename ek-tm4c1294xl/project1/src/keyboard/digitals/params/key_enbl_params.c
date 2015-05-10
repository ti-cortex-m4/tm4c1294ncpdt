/*------------------------------------------------------------------------------
KEY_ENBL_PARAMS,C

 Флаг разрешения опроса мгновенных параметров
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../key_bool.h"


//                                         0123456789ABCDEF
static char const       szMessage[]     = "Параметры ?     ";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetEnblParams(void)
{
  key_SetBool(&flParamsFlag, pszMessages);
}
