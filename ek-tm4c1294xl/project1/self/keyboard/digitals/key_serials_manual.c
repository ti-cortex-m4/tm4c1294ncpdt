/*------------------------------------------------------------------------------
KEY_SERIALS_MANUAL.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../digitals/serials.h"
#include "../common/key_flag.h"
#include "key_serials_manual.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "   ”становка    ",
                        szMessage2[]    = "заводск. номеров",
                        szTrue[]        = " ручна€         ",
                        szFalse[]       = " автоматическа€ ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetSerialsManual(void)
{
  key_SetFlag(&chSerialsManual, pszMessages, szTrue, szFalse);
}
