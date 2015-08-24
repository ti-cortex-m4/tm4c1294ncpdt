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
  ShowChar(bGmtGps);
}



void    key_SetGpsGmt(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if ((bPortGps > 0) && (bPortGps <= bPORTS))
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
        bGmtGps = b;
        SaveCache(&chGmtGps);

        Show();
      }
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
    ShowTimeDateGps(0);


  else if (bKey == bKEY_POINT)
    ShowTimeDateGps(1);


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
