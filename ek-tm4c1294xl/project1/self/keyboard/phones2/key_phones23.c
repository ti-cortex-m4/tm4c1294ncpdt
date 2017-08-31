/*------------------------------------------------------------------------------
KEY_PHONES23.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "phones2.h"



//                                         0123456789ABCDEF
message         code    szUse23         = "    Проверка    ",
                        szPhones23      = "для СМС-контроля";

uchar           *code   pszPhones23[]   = { szUse23, szPhones23, "" };



void    key_SetPhones23(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (UsePhones2())
      {
        enKeyboard = KBD_INPUT1;
        Clear();

        LoadSlide(pszPhones23);
        ShowAnswer();
      }
      else BlockProgram(bSET_PHONES20);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      boDebugPhones2 = boTrue;
      TestPhones2();

      enKeyboard = KBD_INPUT1;
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

        Clear();
        ShowAnswer();
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
*/
