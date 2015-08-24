/*------------------------------------------------------------------------------
KEY_GPS_GMT.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../time/gps.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Часовой пояс    ",
                        szMask[]        = "      ___       ";



static void Show(void)
{
  ShowChar(bGMT);
}



void    key_SetGPS_GMT(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if ((bPortGPS > 0) && (bPortGPS <= bPORTS))
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        ShowHi(szMessage);
        Show();
      }
      else BlockProgram(bSET_GPS_CONFIG);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      uchar b = GetCharLo(6,8);
      if (b <= 13)
      {
        bGMT = b;
        SaveCache(&chGMT);

        Show();
      }
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
    ShowTimeDateGPS(0);


  else if (bKey == bKEY_POINT)
    ShowTimeDateGPS(1);


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
