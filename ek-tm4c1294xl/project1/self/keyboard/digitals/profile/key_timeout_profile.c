/*------------------------------------------------------------------------------
KEY_TIMEOUT_PROFILE!C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_digitals.h"
#include "../../keyboard.h"
#include "../../../display/display.h"
#include "../../../digitals/profile/profile_core.h"
#include "../../../nvram/cache.h"



//                                            0123456789ABCDEF
static char const       szTimeoutProfile[] = "�������: 30 ���.",
                        szMaskChar[]       = "      ___       ";



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
      SaveCache(&chTimeoutProfile);

      ShowChar(bTimeoutProfile);
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
