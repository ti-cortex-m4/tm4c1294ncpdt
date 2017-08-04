/*------------------------------------------------------------------------------
KEY_MONITOR_LOG_CHAR8.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor_settings.h"
#include "../common/key_bool.h"
#include "key_monitor_log_char7.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "Логи монитора в ",
                        szMessage2[]     = "формате CHAR8 ? ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_MonitorLogChar8(void)
{
  key_SetBool(&chMonitorLogChar8, pszMessages);
}
