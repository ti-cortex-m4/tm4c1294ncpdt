/*------------------------------------------------------------------------------
key_profile_interval_direct.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/profile/profile_interval.h"
#include "../../common/key_char_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "    Таймаут     ",
                        szMessage2[]     = "  до перехода   ",
                        szMessage3[]     = " через получас  ",
                        szMessage4[]     = "по прямой связи ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetProfileIntervalDirect(void)
{
  key_SetCharBlocked(&chProfileIntervalDirect, pszMessages, 1, 250, boProfileInterval, wSET_PROFILE_INTERVAL);
}
