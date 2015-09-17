/*------------------------------------------------------------------------------
KEY_MODEMS2.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "keyboard.h"
#include        "speed.h"
#include        "ports.h"
#include        "status.h"
#include        "modems2.h"


//                                         0123456789ABCDEF
message         code    szModemsQuality = "Качество сигнала";


void    key_GetModemsQuality(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      ShowHi(szModemsQuality);

      enKeyboard = KBD_INPUT1;
      Port();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibX = GetChar(10,11) - 1;
      if (ibX < bPORTS)
      {
        enKeyboard = KBD_SHOW;

        ShowModemQuality(ibX);
        SetCurr(DEV_BEGIN);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_SHOW)
    {
      ShowModemQuality(ibX);
      SetCurr(DEV_BEGIN);
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
  }
  else Beep();
}
*/
