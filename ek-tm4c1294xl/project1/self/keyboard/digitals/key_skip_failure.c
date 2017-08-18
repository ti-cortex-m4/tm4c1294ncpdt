/*------------------------------------------------------------------------------
KEY_SKIP_FAILURE,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/skip_failure.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = " Запрет ответа  ",
                        szMessage2[]    = "   на запросы   ",
                        szMessage3[]    = "во время опроса ",
                        szMessage4[]    = "   счетчиков    ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetSkipFalure(void)
{
  key_SetBool(&chSkipFailure, pszMessages);
}
