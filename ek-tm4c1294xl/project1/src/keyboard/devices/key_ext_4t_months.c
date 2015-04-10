/*------------------------------------------------------------------------------
KEY_EXT_4T_MONTHS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../devices/extended_4t.h"
#include        "../key_char.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " ����� �������  ",
                        szMessage2[]     = "  ��� ��������  ",
                        szMessage3[]     = "����. ��������� ",
                        szMessage4[]     = "   �� ������    ",
                        szMessage5[]     = "    �������     ",
                        szMessage6[]     = "  �� ������� ?  ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szMessage6, szCharLimits, "" };



void    key_SetExt4TMonths(void)
{
  key_SetChar(&flExt4TMonths, pszMessages, 0, 12);
}
