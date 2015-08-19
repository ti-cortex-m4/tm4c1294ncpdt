/*------------------------------------------------------------------------------
KEY_PLC_U_FLAG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../devices/devices_init.h"
#include "../common/key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " Èםעונפויס PLC  ",
                        szMessage2[]     = "  הכÿ CE301 ?   ";

static char const       *pszMessages[] = { szMessage1, szMessage2, "" };



void    key_SetPlcUFlag(void)
{
  key_SetBool(&chPlcUFlag, pszMessages);
}
