/*------------------------------------------------------------------------------
KEY_ENBL_CURRENT.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_digitals.h"
#include "../../../digitals/profile/profile_core.h"
#include "../../common/key_bool.h"
#include "key_enbl_current.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   Загружать    ",
                        szMessage2[]     = " 3-мин. данные ?";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_SetEnblCurrent(void)
{
  key_SetBool(&chEnblCurrent, pszMessages);
}
