/*------------------------------------------------------------------------------
KEY_LOGICAL,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../console.h"
#include "../access.h"
#include "../flash/files.h"
#include "../settings.h"



//                                         0123456789ABCDEF
static char const       szLogical[]     = "Логический номер",
                        szMask[]        = "      ___       ";



void    key_SetLogical(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ShowHi(szLogical);
      ShowChar(bLogical);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      bLogical = GetCharLo(6,8);
      SaveFile(&flLogical);

      ShowChar(bLogical);
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
