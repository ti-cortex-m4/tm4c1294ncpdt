/*------------------------------------------------------------------------------
KEY_GPS_SEASON.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/gps.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = " GPS учитывает  ",
                        szMessage2[]    = "сезонное время ?";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetGPSSeason(void)
{
  key_SetBool(&chSeasonGPS, pszMessages);
}
