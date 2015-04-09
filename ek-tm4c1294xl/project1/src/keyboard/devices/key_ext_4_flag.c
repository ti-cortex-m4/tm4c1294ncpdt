/*------------------------------------------------------------------------------
KEY_EXT_4_FLAG.C


------------------------------------------------------------------------------*/

#include        "../../../main.h"
#include        "../../../devices/extended_4.h"
#include        "../../key_flag.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   Загружать    ",
                        szMessage2[]     = "знач. счетчиков ",
                        szMessage3[]     = "   на начало    ",
                        szMessage4[]     = "   месяцев ?    ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetExt4Flag(void)
{
  key_SetFlag(&flExt4Flag, pszMessages);
}
