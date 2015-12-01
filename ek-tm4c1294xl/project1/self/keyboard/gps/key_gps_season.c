/*------------------------------------------------------------------------------
KEY_GPS_SEASON.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/gps.h"
#include "../common/key_bool_blocked.h"
#include "key_gps_season.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " Сезонное время ",
                        szMessage2[]     = "   для GPS ?    ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_SetGpsSeason(void)
{
  key_SetBoolBlocked(&chSeasonGps, pszMessages, UseGps(), bSET_GPS_CONFIG);
}
