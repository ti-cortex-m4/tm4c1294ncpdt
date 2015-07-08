/*------------------------------------------------------------------------------
KEY_ENBL_KEYS,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/digitals.h"
#include "../key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Пароли ?        ";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetEnblKeys(void)
{
  key_SetBool(&chEnblKeys, pszMessages);
}
