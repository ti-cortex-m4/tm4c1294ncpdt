/*------------------------------------------------------------------------------
KEY_TIME_ZONE34.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "key_time_zone34.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "Часовой пояс    ",
                        szMask[]        = "      ___       ";



static void Show(void)
{
  ShowChar(bGmtGps);
}



void    key_SetTimeZone34(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (UseGps())
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
      else Beep();
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
