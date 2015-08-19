/*------------------------------------------------------------------------------
KEY_EXT_6_FLAG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_6.h"
#include "../common/key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "  Прямой опрос  ",
                        szMessage2[]     = "знач. счетчиков ",
                        szMessage3[]     = "на начало суток ",
                        szMessage4[]     = " ABB ЕвроАльфа, ",
                        szMessage5[]     = " Elster A1140 ? ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, "" };



void    key_SetExt6Flag(void)
{
  key_SetBool(&chExt6Flag, pszMessages);
}
