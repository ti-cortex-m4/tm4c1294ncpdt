/*------------------------------------------------------------------------------
KEY_MACHINES_ESC,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../output/esc/esc.h"
#include "../common/key_char.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "    Емкость     ",
                        szMessage2[]     = "протокола Esc ? ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szNumberLimits, "" };



void    key_SetMachinesEsc(void)
{
  key_SetChar(&chMachinesEsc, pszMessages, 1, bMAXMACHINES);
}
