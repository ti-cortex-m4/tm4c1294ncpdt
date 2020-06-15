/*------------------------------------------------------------------------------
KEY_CONTROL_Q.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Контроль времени",
                        szMessage2[]    = "    для CE3xx   ",
                        szTrue[]        = " установка      ",
                        szFalse[]       = " коррекция      ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetControlQ(void)
{
  key_SetFlag(&chControlQ, pszMessages, szTrue, szFalse);
}

