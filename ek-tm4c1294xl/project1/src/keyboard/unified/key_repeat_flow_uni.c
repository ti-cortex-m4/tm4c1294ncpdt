/*------------------------------------------------------------------------------
KEY_REPEAT_FLOW_UNI.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../output/unified/uni.h"
#include "../key_flag.h"



//                                            0123456789ABCDEF
static char const       szRepeatFlowUni1[] = "  Возобновлять  ",
                        szRepeatFlowUni2[] = "транзит УПИО при",
                        szRepeatFlowUni3[] = "каждом запросе ?";

static char const       *pszRepeatFlowUni[]  = { szRepeatFlowUni1, szRepeatFlowUni2, szRepeatFlowUni3, "" };



void    key_SetRepeatFlowUni(void)
{
  key_SetFlag(&flRepeatFlowUni, pszRepeatFlowUni);
}
