/*------------------------------------------------------------------------------
_PHONES30.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"



//                                         0123456789ABCDEF
message         code    szUse20         = "     Модем      ",
                        szUsePhones20   = "для СМС-контроля",
                        szMaskPhones20  = "      ___       ";


uchar           *code   pszPhones20[]   = { szUse20, szUsePhones20, "" };



void    ShowPhones20(void)
{
  ShowChar(bPortPhones2);
  sprintf(szLo+2,"порт:");
  (bPortPhones2 == 0) ? sprintf(szLo+13,"нет") : sprintf(szLo+13,"да ");
}


void    key_SetPhones20(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      LoadSlide(pszPhones20);
      Clear();

      ShowPhones20();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetChar(6,8);
      if (ibX == 0)
      {
        bPortPhones2 = 0;
        ShowPhones20();
      }
      else if (ibX <= bPORTS)
      {
        bPortPhones2 = ibX;
        ShowPhones20();
      }
      else
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskPhones20);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskPhones20);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}
*/
