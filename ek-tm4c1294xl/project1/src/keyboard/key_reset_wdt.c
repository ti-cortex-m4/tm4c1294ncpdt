/*------------------------------------------------------------------------------
KEY_RESET_WDT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "driverlib/watchdog.h"
#include "inc/hw_memmap.h"
#include "key_reset_wdt.h"



//                                         0123456789ABCDEF
static char const       szResetWDT[]    = "—брос по WDT ?  ";



void    key_ResetWDT(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      enKeyboard = KBD_INPUT1;

      ShowHi(szResetWDT);

      Clear();
      ShowAnswer();
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      Waiting();
      LongBeep();
      Clear();

      while (1)
      {
        sprintf(szLo+4,"%8lX", WatchdogValueGet(WATCHDOG0_BASE));
      }
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        if (enKeyboard == KBD_INPUT1)
          enKeyboard = KBD_POSTINPUT1;
        else
          enKeyboard = KBD_INPUT1;

        ShowAnswer();
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
