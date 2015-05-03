/*------------------------------------------------------------------------------
RUN_PROFILE.Ñ


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_profile.h"
#include "../../keyboard.h"
#include "../../../display/display.h"
#include "../../../realtime/realtime.h"
#include "../../../digitals/profile/profile_run.h"



void    key_RunProfile(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      boManualProfile = TRUE;
      fProfile = 0;
      RunProfile(1);
    }
  }
}

