/*------------------------------------------------------------------------------
KEY_EXT_6_FLAG.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../devices/extended_6.h"
#include "../key_flag.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "  ������ �����  ",
                        szMessage2[]     = "����. ��������� ",
                        szMessage3[]     = "�� ������ ����� ",
                        szMessage4[]     = " ABB ���������, ",
                        szMessage5[]     = " Elster A1140 ? ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, "" };



void    key_SetExt6Flag(void)
{
  key_SetFlag(&flExt6Flag, pszMessages);
}
