/*------------------------------------------------------------------------------
KEY_CUSTOM_MODEM!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/phones.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Выдавать модему ",
                        szMessage2[]    = " настройки 2 ?  ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetCustomModem(void)
{
  key_SetBool(&chCustomModem, pszMessages);
}
