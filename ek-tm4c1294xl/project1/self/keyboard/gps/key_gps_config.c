/*------------------------------------------------------------------------------
KEY_GPS_CONFIG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../serial/speeds.h"
#include "../../serial/speeds_display.h"
#include "../../time/gps.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Задание GPS     ",
                        szMask[]        = "      ___       ";



static void Show(void)
{
  (bPortGps == 0) ? sprintf(szHi+11,": нет") : sprintf(szHi+11,": да ");
  ShowChar(bPortGps);
  sprintf(szLo+2,"порт:");
}


void    key_SetGpsConfig(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szMessage);
      Clear();

      Show();
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      uchar bPrt = GetCharLo(6,8);
      if (bPrt == 0)
      {
        bPortGps = 0;
        SaveCache(&chPortGps);

        Show();
      }
      else if (bPrt <= bPORTS)
      {
        if (StreamPortDirect(bPrt-1) == 0)
        {
          bPortGps = 0;
          SaveCache(&chPortGps);

          Show();
        }
        else
        {
          bPortGps = bPrt;
          SaveCache(&chPortGps);

          Show();

          uchar ibPrt = bPrt - 1;
          mppoPorts[ibPrt].ibBaud = 3;
          mppoPorts[ibPrt].ibParity = 0;
          SetSpeed(ibPrt);
          SetDefaultDelay(ibPrt);
        }
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMask);
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
