/*------------------------------------------------------------------------------
KEY_DSBL_REFILL.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/profile/refill.h"
#include "../../key_flag.h"



//                                          0123456789ABCDEF
static char const       szDsblRefill1[]  = " Запрет очистки ",
                        szDsblRefill2[]  = "пустых профилей ",
                        szDsblRefill3[]  = "для Меркурий-230";

static char const       *pszDsblRefill[] = { szDsblRefill1, szDsblRefill2, szDsblRefill3, "" };



void    key_SetDsblRefill(void)
{
  key_SetBool(&flDsblRefill, pszDsblRefill);
}
