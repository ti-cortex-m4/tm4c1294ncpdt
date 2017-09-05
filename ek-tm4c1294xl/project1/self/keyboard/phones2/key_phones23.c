/*------------------------------------------------------------------------------
KEY_PHONES23.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_phones.h"
#include "../../memory/mem_ports.h"
#include "../../digitals/phones2/phones2.h"
#include "../../digitals/phones2/phones2_facade.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "    Проверка    ",
                        szMessage2[]    = "для СМС-контроля";

static char const      *pszMessages[]   = { szMessage1, szMessage2, "" };



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

        LoadSlide(pszMessages);
        ShowAnswer();
      }
      else BlockProgram(bSET_PHONES20);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
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
