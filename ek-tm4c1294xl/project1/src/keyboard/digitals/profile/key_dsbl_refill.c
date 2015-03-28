/*------------------------------------------------------------------------------
KEY_DSBL_REFILL.C


------------------------------------------------------------------------------*/

#include        "../../../main.h"
//#include        "../../../memory/mem_digitals.h"
//#include        "../../digitals/profile_core.h"
#include        "../../key_flag.h"



//                                          0123456789ABCDEF
static char const       szDsblRefill1[]  = " ������ ������� ",
                        szDsblRefill2[]  = "������ �������� ",
                        szDsblRefill3[]  = "��� ��������-230";

static char const       *pszDsblRefill[] = { szDsblRefill1, szDsblRefill2, szDsblRefill3, "" };



void    key_SetDsblRefill(void)
{
  key_SetFlag(&flDsblRefill, pszDsblRefill);
}
