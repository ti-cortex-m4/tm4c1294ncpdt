/*------------------------------------------------------------------------------
KEY_MAX_DELAY_UNI.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../output/unified/uni.h"
#include "../common/key_char.h"


//                                         0123456789ABCDEF
static char const       szMaxDelayUni[] = "  “‡ÈÏ‡ÛÚ ”œ»Œ  ";

static char const       *pszMaxDelayUni[] = { szMaxDelayUni, szNumberLimits, "" };



void    key_SetMaxDelayUni(void)
{
  key_SetChar(&chMaxDelayUni, pszMaxDelayUni, 10, 250);
}
