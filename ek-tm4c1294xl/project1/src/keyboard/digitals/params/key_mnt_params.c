/*------------------------------------------------------------------------------
KEY_MNT_PARAMS,C


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/params/params.h"
#include "../../key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "¬рем€ обновлени€",
                        szMessage2[]    = " дл€ параметров ",
                        szTrue[]        = " 3 минуты       ",
                        szFalse[]       = " 30 минут       ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetMntParams(void)
{
  key_SetFlag(&flMntParams, pszMessages, szTrue, szFalse);
}
