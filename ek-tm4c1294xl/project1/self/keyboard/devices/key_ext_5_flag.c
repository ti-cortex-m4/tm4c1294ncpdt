/*------------------------------------------------------------------------------
KEY_EXT_5_FLAG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_5.h"
#include "../common/key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   Загружать    ",
                        szMessage2[]     = "знач. счетчиков ",
                        szMessage3[]     = "  по тарифам ?  ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetExt5Flag(void)
{
  key_SetBool(&chExt5Flag, pszMessages);
}
