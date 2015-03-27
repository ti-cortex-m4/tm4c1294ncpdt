/*------------------------------------------------------------------------------
_LIMITS.C

 
------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"



//                                          0123456789ABCDEF
message         code    szLimits         = "Верхняя граница ",
                        szMaskLimits     = "    ____     ";

                        

void    ShowLimits(void)
{
  Clear();
  sprintf(szLo+4,"%04u:%02bu",mpcwStopCan[ibX],(uchar)(mpcwStopCan[ibX]/48 + 1));

  sprintf(szLo+14,"%2bu",ibX+1);
}



void    key_SetLimits(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szLimits);

      Canal();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowLimits();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowLimits();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;
      ShowLimits();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((iwA = GetInt(4,7) - 1) < wHOURS)
      {
        enKeyboard = KBD_POSTENTER;

        mpcwStopCan[ibX] = iwA + 1;
        ShowLimits();
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
      ShowLimits();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT2;
      ShowLo(szMaskLimits);
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

