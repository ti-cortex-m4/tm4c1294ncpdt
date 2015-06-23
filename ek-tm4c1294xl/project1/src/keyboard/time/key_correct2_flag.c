/*------------------------------------------------------------------------------
KEY_CORRECT_2_FLAG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/correct2.h"
#include "../key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "��������� �����",
                        szMessage2[]     = "   ���������   ",
                        szMessage3[]     = "   ���������   ",
                        szMessage4[]     = "   ������� ?   ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetCorrect2Flag(void)
{
  key_SetBool(&chCorrect2Flag, pszMessages);
}
