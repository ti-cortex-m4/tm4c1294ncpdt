/*------------------------------------------------------------------------------
KEY_TIMEOUT_CURRENT.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/profile/profile_core.h"
#include        "../../flash/files.h"



//                                            0123456789ABCDEF
static char const       szTimeoutCurrent[] = "Таймаут: 3 мин. ",
                        szMaskChar[]       = "      ___       ";



void    key_SetTimeoutCurrent(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ShowHi(szTimeoutCurrent);
      ShowChar(bTimeoutCurrent);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      bTimeoutCurrent = GetCharLo(6,8);
      SaveFile(&flTimeoutCurrent);

      ShowChar(bTimeoutCurrent);
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskChar);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}
