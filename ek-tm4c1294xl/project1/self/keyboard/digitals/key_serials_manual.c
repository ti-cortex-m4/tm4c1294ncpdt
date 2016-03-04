/*------------------------------------------------------------------------------
KEY_SERIALS_MANUAL.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digital/digitals.h"
#include "../common/key_bool.h"
#include "key_serials_manual.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Ручная установка",
                        szMessage2[]    = "заводск. номеров";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetSerialsManual(void)
{
  key_SetBool(&chSerialsManual, pszMessages);
}
