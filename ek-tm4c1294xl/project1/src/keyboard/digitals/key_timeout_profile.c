/*------------------------------------------------------------------------------
KEY_TIMEOUT_PROFILE.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/profile_core.h"
#include        "../../flash/files.h"



//                                                0123456789ABCDEF
static char const       szTimeoutProfile[]     = "Таймаут: 30 мин.",
                        szMaskTimeoutProfile[] = "      ___       ";



void    key_SetTimeoutProfile(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ShowHi(szTimeoutProfile);
      ShowChar(bTimeoutProfile);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      bTimeoutProfile = GetCharLo(6,8);
      SaveFile(&flTimeoutProfile);
      ShowChar(bTimeoutProfile);
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskTimeoutProfile);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}
