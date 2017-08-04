/*------------------------------------------------------------------------------
KEY_MONITOR_LOG_HEX.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor_settings.h"
#include "../common/key_bool.h"
#include "key_monitor_log_hex.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "Логи монитора в ",
                        szMessage2[]     = " формате HEX ?  ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_MonitorLogHex(void)
{
  key_SetBool(&chMonitorLogHex, pszMessages);
}
