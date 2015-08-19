/*------------------------------------------------------------------------------
KEY_PLC_U_FLAG,C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/profile/refill.h"
#include "../../key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " Запрет очистки ",
                        szMessage2[]     = "пустых профилей ",
                        szMessage3[]     = "для Меркурий-230";

static char const       *pszDsblRefill[] = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetPlcUFlag(void)
{
  key_SetBool(&chDsblRefill, pszDsblRefill);
}
