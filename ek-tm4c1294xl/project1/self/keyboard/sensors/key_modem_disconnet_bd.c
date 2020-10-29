/*------------------------------------------------------------------------------
KEY_MODEM_DISCONNECT_BD!C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Разъединять   ",
                        szMessage2[]    = "  модем между   ",
                        szMessage3[]    = "    опросом     ",
                        szMessage4[]    = "   счетчиков    ",
                        szMessage5[]    = "на том же самом ",
                        szMessage6[]    = "    номере ?    ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szMessage6, "" };



void    key_SetModemDisconnectBD(void)
{
  key_SetBool(&chModemDisconnectBetweenDigitals, pszMessages);
}
