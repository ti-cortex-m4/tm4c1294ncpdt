/*------------------------------------------------------------------------------
KEY_TEST_MONITOR.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../access.h"
#include "../../serial/monitor.h"
#include "key_test_monitor.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Монитор         ";



void    key_TestMonitor(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szMessage);
      Clear();
    }
  }
  else if (bKey == bKEY_MINUS)
  {
    MonitorClose();
  }
  else Beep();
}


void    auto_TestMonitor(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
    (SuperUser()) ? (szHi[10] = '+') : (szHi[10] = '-');

    uint w = GetMonitorDelay();

    Hi(12, w / 0x100);
    Hi(14, w % 0x100);
  }
}
