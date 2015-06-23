/*------------------------------------------------------------------------------
KEY_CONTROL_TIME.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_digitals.h"
#include "../../../devices/devices_init.h"
#include "../../key_bool.h"



//                                         0123456789ABCDEF
static char const       szControl[]     = "   Коррекция    ",
                        szTime[]        = "времени и даты ?";

static char const       *pszControlTime[] = { szControl, szTime, "" };



void    key_SetControlTime(void)
{
  key_SetBool(&chControlTime, pszControlTime);
}
