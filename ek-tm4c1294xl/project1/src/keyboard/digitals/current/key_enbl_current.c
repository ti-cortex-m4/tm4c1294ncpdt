/*------------------------------------------------------------------------------
KEY_ENBL_CURRENT,C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_digitals.h"
#include "../../../digitals/profile/profile_core.h"
#include "../../key_flag.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   Загружать    ",
                        szMessage2[]     = " 3-мин. данные ?";

static char const       *pszMessage[]    = { szMessage1, szMessage2, "" };



void    key_SetEnblCurrent(void)
{
  key_SetBool(&flEnblCurrent, pszMessage);
}
