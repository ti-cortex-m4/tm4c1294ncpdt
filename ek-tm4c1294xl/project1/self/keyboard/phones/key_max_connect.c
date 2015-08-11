/*------------------------------------------------------------------------------
KEY_MAX_CONNECT.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/phones.h"
#include "../key_char.h"



//                                            0123456789ABCDEF
static char const       szMessage1[]       = "Время соединения";

static char const       *pszMessages[]   = { szMessage1, szCharLimits, "" };



void    key_SetMaxConnect(void)
{
  key_SetChar(&chMaxConnect, pszMessages, 1, 180);
}
