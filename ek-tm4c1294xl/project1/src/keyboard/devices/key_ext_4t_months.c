/*------------------------------------------------------------------------------
KEY_EXT_4T_MONTHS,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_4t.h"
#include "../key_char_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " „исло мес€цев  ",
                        szMessage2[]     = "  дл€ загрузки  ",
                        szMessage3[]     = "знач. счетчиков ",
                        szMessage4[]     = "   на начало    ",
                        szMessage5[]     = "    мес€цев     ",
                        szMessage6[]     = "  по тарифам ?  ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szMessage6, szCharLimits, "" };



void    key_SetExt4TMonths(void)
{
	key_SetCharBlocked(&flExt4TMonths, pszMessages, 1, 12, boExt4TFlag, wSET_EXT4T_FLAG);
}
