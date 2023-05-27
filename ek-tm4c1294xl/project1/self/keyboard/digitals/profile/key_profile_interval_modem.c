/*------------------------------------------------------------------------------
key_profile_interval_modem.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/profile/profile_interval.h"
#include "../../common/key_char_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "    Таймаут     ",
                        szMessage2[]     = "  до перехода   ",
                        szMessage3[]     = " через получас  ",
                        szMessage4[]     = "по модемн. связи";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetProfileIntervalModem(void)
{
  key_SetCharBlocked(&chProfileIntervalModem, pszMessages, 1, 250, boProfileInterval, wSET_PROFILE_INTERVAL);
}
