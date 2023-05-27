/*------------------------------------------------------------------------------
key_profile_interval.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/profile/profile_interval.h"
#include "../../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Приостанавливать",
                        szMessage2[]    = "     опрос      ",
                        szMessage3[]    = "  при переходе  ",
                        szMessage4[]    = " через получас  ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetProfileInterval(void)
{
  key_SetBool(&chProfileInterval, pszMessages);
}
