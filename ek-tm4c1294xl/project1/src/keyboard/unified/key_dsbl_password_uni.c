/*------------------------------------------------------------------------------
KEY_DSBL_PASSWORD_UNI.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../output/unified/uni.h"
#include "../key_flag.h"



//                                              0123456789ABCDEF
static char const       szDsblPasswordUni1[] = "   Пароль для   ",
                        szDsblPasswordUni2[] = "протокола УПИО ?";

static char const       *pszDsblPasswordUni[] = { szDsblPasswordUni1, szDsblPasswordUni2, "" };



void    key_SetDsblPasswordUni(void)
{
  key_SetFlag(&flDsblPasswordUni, pszDsblPasswordUni);
}
