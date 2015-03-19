/*------------------------------------------------------------------------------
KEY_MAX_CONNECT.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_phones.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/phones.h"
#include        "../../flash/files.h"



//                                            0123456789ABCDEF
static char const       szMaxConnect[]     = "Время соединения",
                        szMaskChar[]       = "      ___       ";



void    key_SetMaxConnect(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      ShowHi(szMaxConnect);
      ShowChar(bMaxConnect);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetCharLo(6,8);
      if ((ibX != 0) && (ibX <= 180))
      {
        bMaxConnect = ibX;
        SaveFile(&flMaxConnect);

        ShowChar(bMaxConnect);
      }
      else
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskChar);
      }
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
