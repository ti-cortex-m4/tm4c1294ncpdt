/*------------------------------------------------------------------------------
KEY_ENBL_PARAMS.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../key_flag.h"


//                                         0123456789ABCDEF
static char const       szEnblParams[]  = "Параметры ?     ";

static char const       *pszEnblParams[] = { szEnblParams, "" };



void    key_SetEnblParams(void)
{
  key_SetFlag(&flEnblAllParams, pszEnblParams);
}
