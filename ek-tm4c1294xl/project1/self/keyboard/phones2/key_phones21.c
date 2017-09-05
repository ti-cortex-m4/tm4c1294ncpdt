/*------------------------------------------------------------------------------
KEY_PHONES21.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_phones.h"
#include "../../memory/mem_ports.h"
#include "../../digitals/phones2/phones2.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = " Лимит мощности ",
                        szMessage2[]    = "для СМС-контроля",
                        szMask[]        = "_________ ___";

static char const      *pszMessages[]   = { szMessage1, szMessage2, "" };



static void Show(void)
{
  ShowFloat(reMaxxPhones2);
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
        LoadSlide(pszMessages);

        Show();
      }
      else BlockProgram(bSET_PHONES20);
    }
    else if ((enKeyboard == KBD_POSTINPUT2) || (enKeyboard == KBD_POSTINPUT3))
    {
      float fl = GetRealLo(0,8) + GetRealLo(10,12)/1000;

      if (fl > 0)
      {
        enKeyboard = KBD_POSTENTER;
        reMaxxPhones2 = fl;
      }
      else Beep();

      if (enKeyboard == KBD_POSTENTER)
        Show();
      else
      {
        enKeyboard = KBD_INPUT2;
        LongBeep();

        ShowLo(szMask);
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
      ShowLo(szMask);
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
