/*------------------------------------------------------------------------------
KEY_PHONES21.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "engine.h"
#include        "phones2.h"



//                                         0123456789ABCDEF
message         code    szUse21         = " Лимит мощности ",
                        szPhones21      = "для СМС-контроля",
                        szMaskPhones21  = "_________ ___";

uchar           *code   pszPhones21[]  = { szUse21, szPhones21, "" };



void    ShowPhones21(void)
{
  LoadSlide(pszPhones21); ShowReal(&reMaxxPhones2);
}



void    key_SetPhones21(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (UsePhones2())
      {
        enKeyboard = KBD_POSTENTER;
        ShowPhones21();
      }
      else BlockProgram(bSET_PHONES20);
    }
    else if ((enKeyboard == KBD_POSTINPUT2) || (enKeyboard == KBD_POSTINPUT3))
    {
      reBuffA = *PGetReal(0,8) + *PGetReal(10,12)/1000;

      if (reBuffA > 0)
      {
        enKeyboard = KBD_POSTENTER;
        reMaxxPhones2 = reBuffA;
      }
      else Beep();

      if (enKeyboard == KBD_POSTENTER)
        ShowPhones21();
      else
      {
        enKeyboard = KBD_INPUT2;
        LongBeep();

        ShowLo(szMaskPhones21);
      }
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT3;
      szLo[9] = '.';
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT2;
      ShowLo(szMaskPhones21);
    }

    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(0,8);
    }
    else
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(10,12);
    }
  }
  else Beep();
}
*/
