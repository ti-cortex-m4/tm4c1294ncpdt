/*------------------------------------------------------------------------------
KEY_MAX_CONNECT!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/phones.h"
#include "../common/key_char.h"



//                                            0123456789ABCDEF
static char const       szMessage1[]       = "����� ����������";

static char const       *pszMessages[]   = { szMessage1, szNumberLimits, "" };



void    key_SetMaxConnect(void)
{
  key_SetChar(&chMaxConnect, pszMessages, 1, 180);
}
