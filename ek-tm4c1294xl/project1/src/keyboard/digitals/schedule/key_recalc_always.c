/*------------------------------------------------------------------------------
KEY_RECALC_ALWAYS.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_schedule.h"
#include "../../../digitals/schedule/schedule.h"
#include "../../key_flag.h"



  //                                         0123456789ABCDEF
static char const       szRecalcAlways1[] = " Полный расчет  ",
                        szRecalcAlways2[] = "~нергии/мощности";


static char const       *pszRecalcAlways[] = { szRecalcAlways1, szRecalcAlways2, "" };



void    key_SetRecalcAlways(void)
{
  key_SetBool(&flRecalcAlways, pszRecalcAlways);
}
