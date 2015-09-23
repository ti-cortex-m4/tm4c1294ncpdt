/*------------------------------------------------------------------------------
KEY_CORRECT3_FLAG!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/gps.h"
#include "../../time/correct3.h"
#include "../common/key_bool_blocked.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Учет работы GPS ",
                        szMessage2[]    = " при коррекции  ",
                        szMessage3[]    = "   времени ?    ";

static char const      *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetCorrect3Flag(void)
{
  key_SetBoolBlocked(&chCorrect3Flag, pszMessages, UseGps(), bSET_GPS_CONFIG);
}
