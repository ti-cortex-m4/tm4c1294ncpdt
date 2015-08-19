/*------------------------------------------------------------------------------
KEY_EXT_4_MONTHS,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_4.h"
#include "../key_char_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " „исло мес€цев  ",
                        szMessage2[]     = "  дл€ загрузки  ",
                        szMessage3[]     = "знач. счетчиков ",
                        szMessage4[]     = "   на начало    ",
                        szMessage5[]     = "   мес€цев ?    ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szNumberLimits, "" };



void    key_SetExt4Months(void)
{
  key_SetCharBlocked(&chExt4Months, pszMessages, 1, 12, fExt4Flag, bSET_EXT4_FLAG);
}
