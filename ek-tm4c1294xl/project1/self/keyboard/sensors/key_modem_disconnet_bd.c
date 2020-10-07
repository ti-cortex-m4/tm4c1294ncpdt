/*------------------------------------------------------------------------------
KEY_MODEM_DISCONNECT_BD!C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../../sensors/sensor2/profile2x16.h"
#include "../common/key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Размер блока  ",
                        szMessage2[]    = "   при опросе   ",
                        szMessage3[]    = "  Меркурий-230  ",
                        szTrue[]        = " 1 получас      ",
                        szFalse[]       = " 16 получасов   ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetModemDisconnectBD(void)
{
  key_SetFlag(&chShortProfileB, pszMessages, szTrue, szFalse);
}
