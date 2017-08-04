/*------------------------------------------------------------------------------
KEY_MONITOR_LOG_BASIC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor_settings.h"
#include "../common/key_bool.h"
#include "key_monitor_log_basic.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " Логи монитора: ",
                        szMessage2[]     = " время/длинна ? ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_MonitorLogBasic(void)
{
  key_SetBool(&chMonitorLogBasic, pszMessages);
}
