/*------------------------------------------------------------------------------
KEY_MONITOR_RUN.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../console.h"
#include "key_monitor_run.h"



//                                          0123456789ABCDEF
static char const       szPortFrom[]     = "Транзит: запуск ",
                        szPortTo[]       = "Транзит: порт   ",
                        szMaskPortTo[]   = "      ___       ";



void    key_MonitorRun(void)
{
static uchar ibPrt;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szPortFrom);

      Port();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibPrt = GetCharLo(10,11) - 1) < bPORTS)
      {
        if ((ibPrt == 0) || (ibPrt == 1))
        {
          StartMonitor(ibPrt);
          OK();
        }
        else
        {
          Error();
          LongBeep();
        }
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}
