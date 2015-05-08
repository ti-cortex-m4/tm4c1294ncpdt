/*------------------------------------------------------------------------------
KEY_MACHINES_ESC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../output/esc/esc.h"
#include "../key_char.h"



//                                          0123456789ABCDEF
static char const       szMessage[]      = "Емкость: Esc    ";

static char const       *pszMessages[]   = { szMessage, "" };



void    key_SetMachinesEsc(void)
{
  key_SetChar(&flMachinesEsc, pszMessages, 1, bMAXMACHINES);
}
