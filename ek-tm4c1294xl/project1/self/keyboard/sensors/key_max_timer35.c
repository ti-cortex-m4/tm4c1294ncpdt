/*------------------------------------------------------------------------------
KEY_MAX_TIMER35.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_char.h"
#include "key_max_timer35.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Макс. время   ",
                        szMessage2[]    = "ожидания ответа ",
                        szMessage3[]    = "  CExxx NNCL2   ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szNumberLimits, "" };



void    key_SetMaxTimer35(void)
{
  key_SetChar(&chMaxTimer35, pszMessages, 60, 250);
}
