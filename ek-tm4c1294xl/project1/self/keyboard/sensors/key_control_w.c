/*------------------------------------------------------------------------------
KEY_CONTROL_W.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Контроль времени",
                        szMessage2[]    = "для Rovalant МЭС",
                        szTrue[]        = " установка      ",
                        szFalse[]       = " коррекция      ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetControlW(void)
{
  key_SetFlag(&chControlW, pszMessages, szTrue, szFalse);
}

