/*------------------------------------------------------------------------------
key_ignore_status38.c


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Игнорировать  ",
                        szMessage2[]    = " статус ответа  ",
                        szMessage3[]    = "  для СЕ318 ?   ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetIgnoreStatus38(void)
{
  key_SetBool(&chIgnoreStatus38, pszMessages);
}
