/*------------------------------------------------------------------------------
KEY_EXT_4T_MONTHS,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_4t.h"
#include "../common/key_char_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " ����� �������  ",
                        szMessage2[]     = "  ��� ��������  ",
                        szMessage3[]     = "����. ��������� ",
                        szMessage4[]     = "   �� ������    ",
                        szMessage5[]     = "    �������     ",
                        szMessage6[]     = "  �� ������� ?  ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szMessage6, szNumberLimits, "" };



void    key_SetExt4TMonths(void)
{
	key_SetCharBlocked(&chExt4TMonths, pszMessages, 1, 12, fExt4TFlag, wSET_EXT4T_FLAG);
}
