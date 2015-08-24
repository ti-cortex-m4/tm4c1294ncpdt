/*------------------------------------------------------------------------------
KEY_GPS_CONFIG.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "display.h"
#include        "keyboard.h"
#include        "speed.h"
#include        "timedate.h"
#include        "gps.h"



//                                         0123456789ABCDEF
message         code    szGPSConfig     = "Задание GPS     ",
                        szMaskGPSConfig = "      ___       ";



void    ShowGPS(void)
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

      ShowHi(szGPSConfig);
      Clear();

      ShowGPS();
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetChar(6,8);
      if (ibX == 0)
      {
        bPortGPS = 0;
        ShowGPS();   
      }
      else if (ibX <= bPORTS)
      {
        if (StreamPortDirect(ibX-1) == 0)
        {
          bPortGPS = 0;
          ShowGPS();   
        }
        else
        {
          bPortGPS = ibX;
          ShowGPS();   

          ibX--;
          mppoPorts[ibX].ibSpeed = 3;
          mppoPorts[ibX].ibParity = 0;
          SetSpeeds(ibX);               
          SetDelay(ibX);
        }
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskGPSConfig);        
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
      ShowLo(szMaskGPSConfig);        
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}

*/
