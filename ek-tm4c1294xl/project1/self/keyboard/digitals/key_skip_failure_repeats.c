/*------------------------------------------------------------------------------
KEY_SKIP_FAILURE_REPEATS!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/skip_failure.h"
#include "../common/key_bool.h"



//                                            0123456789ABCDEF
static char const       szMessage1[]       = "  Повторы при   ",
                        szMessage2[]       = "опросе счетчиков";

static char const       *pszMessages[]     = { szMessage1, szMessage2, szNumberLimits, "" };



void    key_SetSkipFalureRepeats(void)
{
  key_SetChar(&chSkipFailureRepeats, pszMessages, 1, 5);
}
