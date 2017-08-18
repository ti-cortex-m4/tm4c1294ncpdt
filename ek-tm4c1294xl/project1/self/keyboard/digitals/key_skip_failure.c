/*------------------------------------------------------------------------------
KEY_SKIP_FAILURE,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/skip_failure.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Быстрый пропуск ",
                        szMessage2[]    = "  отключенных   ",
                        szMessage3[]    = "   счетчиков    ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetSkipFalure(void)
{
  key_SetBool(&chSkipFailureEnbl, pszMessages);
}
