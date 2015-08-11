/*------------------------------------------------------------------------------
KEY_REPEAT_FLOW_UNI,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../output/unified/uni.h"
#include "../key_bool.h"



//                                            0123456789ABCDEF
static char const       szMessage1[]       = "  Возобновлять  ",
                        szMessage2[]       = "    транзит     ",
                        szMessage3[]       = " протокола УПИО ",
                        szMessage4[]       = "      при       ",
                        szMessage5[]       = "каждом запросе ?";

static char const       *pszMessages[]     = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, "" };



void    key_SetRepeatFlowUni(void)
{
  key_SetBool(&chRepeatFlowUni, pszMessages);
}
