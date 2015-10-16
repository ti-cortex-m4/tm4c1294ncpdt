/*------------------------------------------------------------------------------
KEY_CORRECT2_FLAG.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/correct2.h"
#include "../common/key_bool.h"
#include "key_correct2_flag.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "Парольный режим",
                        szMessage2[]     = "   удаленной   ",
                        szMessage3[]     = "   коррекции   ",
                        szMessage4[]     = "   времени ?   ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetCorrect2Flag(void)
{
  key_SetBool(&chCorrect2Flag, pszMessages);
}
