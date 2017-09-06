/*------------------------------------------------------------------------------
KEY_PHONES30.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_phones.h"
#include "../../memory/mem_ports.h"
#include "../../digitals/phones2/phones2.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "     Модем      ",
                        szMessage2[]    = "для СМС-контроля",
                        szMask[]        = "      ___       ";


static char const      *pszMessages[]   = { szMessage1, szMessage2, "" };



static void Show(void)
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

      LoadSlide(pszMessages);
      Clear();

      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      uchar b = GetCharLo(6,8);
      if (b <= bPORTS)
      {
        bPortPhones2 = b;
        SaveCache(&chPortPhones2);

        Show();
      }
      else
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMask);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMask);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}

