/*------------------------------------------------------------------------------
KEY_MONITOR_LOG_CHAR7.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor_settings.h"
#include "../common/key_bool.h"
#include "key_monitor_log_char7.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " Монитор: лог в ",
                        szMessage2[]     = "формате CHAR7 ? ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_MonitorLogChar7(void)
{
  key_SetBool(&chMonitorLogChar7, pszMessages);
}
