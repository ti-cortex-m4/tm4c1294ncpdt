/*------------------------------------------------------------------------------
KEY_MAX_REPEATS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../digitals/max_repeats.h"
#include        "../key_char.h"



//                                            0123456789ABCDEF
static char const       szMaxRepeats1[]    = "  Повторы при   ",
                        szMaxRepeats2[]    = "опросе счетчиков";

static char const       *pszMaxRepeats[]   = { szMaxRepeats1, szMaxRepeats2, szCharLimits, "" };



void    key_SetMaxRepeats(void)
{
  key_SetChar(&flMaxRepeats, pszMaxRepeats, 1, 20);
}
