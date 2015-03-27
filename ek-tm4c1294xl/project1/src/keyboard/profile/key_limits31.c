/*------------------------------------------------------------------------------
_LIMITS31.C

 
------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "sensors.h"



//                                          0123456789ABCDEF
message         code    szLimits31       = "Нижняя граница  ",
                        szMaskLimits31   = "    ____     ";

                        

void    ShowLimits31(void)
{
  Clear();
  sprintf(szLo+4,"%04u:%02bu",mpcwStartRelCan[ibX],(uchar)(mpcwStartRelCan[ibX]/48 + 1));

  if (GetDigitalDevice(ibX) == 6) 
    szLo[2] = '+';  
  else 
    szLo[2] = ' ';

  sprintf(szLo+14,"%2bu",ibX+1);
}



void    key_SetLimits31(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boStartCan == boTrue)
      {
        enKeyboard = KBD_INPUT1;
        ShowHi(szLimits31);

        Canal();
      }
      else BlockProgram(bSET_LIMITS30);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowLimits31();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowLimits31();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;
      ShowLimits31();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((iwA = GetInt(4,7) - 1) < wHOURS)
      {
        enKeyboard = KBD_POSTENTER;

        mpcwStartRelCan[ibX] = iwA + 1;
        ShowLimits31();
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      (ibX > 0) ? (ibX--) : (ibX = bCANALS - 1);
      ShowLimits31();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT2;
      ShowLo(szMaskLimits31);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(4,7);
    }
    else Beep(); 
  }
  else Beep();
}
*/

