/*------------------------------------------------------------------------------
KEY_PRIVATE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../access.h"
#include        "../settings.h"


//                                         0123456789ABCDEF
static char const       szPrivate[]     = "Заводской номер ",
                        szMaskPrivate[] = "    _____       ";



void    key_SetPrivate(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ShowHi(szPrivate);
      ShowInt(wPrivate);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      wPrivate = GetInt(4,8);
      SavePrivate() ? ShowInt(wPrivate) : Error();
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      if (SuperUser() == 1) 
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szMaskPrivate);
      }
      else LongBeep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(4,8);
    }
  }
  else Beep();
}
