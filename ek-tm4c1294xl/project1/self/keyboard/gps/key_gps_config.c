/*------------------------------------------------------------------------------
KEY_GPS_CONFIG.C


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
  (bPortGPS == 0) ? sprintf(szHi+11,": нет") : sprintf(szHi+11,": да ");
  ShowChar(bPortGPS);
  sprintf(szLo+2,"порт:");
}


void    key_SetGPSConfig(void)
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
        bPortGPS = 0;
        Show();
      }
      else if (bPrt <= bPORTS)
      {
        if (StreamPortDirect(bPrt-1) == 0)
        {
          bPortGPS = 0;
          SaveCache(&chPortGPS);

          Show();
        }
        else
        {
          bPortGPS = bPrt;
          SaveCache(&chPortGPS);

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
