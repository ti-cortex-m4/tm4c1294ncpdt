/*------------------------------------------------------------------------------
KEY_MANAGE_TIME.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_digitals.h"
#include "../../../devices/devices_init.h"
#include "../../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szManage[]      = "Полный контроль ",
                        szTime[]        = "времени и даты ?";

static char const       *pszManageTime[] = { szManage, szTime, "" };




void    key_SetManageTime(void)
{
  key_SetBool(&chManageTime, pszManageTime);
}
