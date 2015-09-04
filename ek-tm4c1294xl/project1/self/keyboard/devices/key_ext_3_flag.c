/*------------------------------------------------------------------------------
KEY_EXT_3_FLAG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_4.h"
#include "../common/key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   Загружать    ",
                        szMessage2[]     = "журналы событий ",
                        szMessage3[]     = " со счетчиков ? ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetExt3Flag(void)
{
  key_SetBool(&chExt4Flag, pszMessages);
}
