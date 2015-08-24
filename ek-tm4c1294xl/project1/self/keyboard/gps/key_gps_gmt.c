/*------------------------------------------------------------------------------
KEY_GPS_GMT.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "display.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "speed.h"
#include        "timedate.h"
#include        "gps.h"



//                                         0123456789ABCDEF
message         code    szSetGPS_GMT    = "Часовой пояс    ",
                        szMaskSetGPS_GMT= "      ___       ";



void    ShowGPS_GMT(void)
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

        ShowHi(szSetGPS_GMT);
        ShowGPS_GMT();
      }
      else BlockProgram(bSET_GPS_CONFIG);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      if ((ibX=GetChar(6,8)) <= 13)
      {
        bGMT = ibX;
        ShowGPS_GMT();   
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
      ShowLo(szMaskSetGPS_GMT);        
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
