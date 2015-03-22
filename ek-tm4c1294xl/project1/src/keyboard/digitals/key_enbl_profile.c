/*------------------------------------------------------------------------------
KEY_ENBL_PROFILE.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../digitals/profile_core.h"
#include        "../key_flag.h"



//                                         0123456789ABCDEF
static char const       szEnbl[]        = "   Загружать    ",
                        szProfile[]     = "30-мин. данные ?";

static char const       *pszEnblProfile[] = { szEnbl, szProfile, "" };



void    key_SetEnblProfile(void)
{
  key_SetFlag(&flEnblProfile, pszEnblProfile);
}
