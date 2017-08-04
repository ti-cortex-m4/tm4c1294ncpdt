/*------------------------------------------------------------------------------
KEY_MAX_SHUTDOWN!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/max_shutdown.h"
#include "../common/key_int.h"



//                                            0123456789ABCDEF
static char const       szMessage1[]       = "  Максимальное  ",
                        szMessage2[]       = "время (получасы)",
                        szMessage3[]       = "   выключения   ",
                        szMessage4[]       = "   счетчиков    ";

static char const       *pszMessages[]     = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetMaxShutdown(void)
{
  key_SetInt(&chMaxShutdown, pszMessages, 48, 480);
}
