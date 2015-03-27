/*------------------------------------------------------------------------------
_LIMITS33.С


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "access.h"
#include        "display.h"
#include        "keyboard.h"



//                                         0123456789ABCDEF
message         code    szFlag33        = "    Признаки    ",
                        szStartCan      = " начала опроса  ";
                     
uchar           *code   pszLimits33[]   = { szFlag33, szStartCan, "" };



void    ShowLimits33(void)
{
  Clear();
  sprintf(szLo+14,"%2bu",ibX+1);

  if (mpboStartCan[ibX] == boFalse) 
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetLimits33(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      LoadSlide(pszLimits33);

      Canal();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowLimits33();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetChar(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowLimits33();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;

      ShowLimits33();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      mpboStartCan[ibX] = ~mpboStartCan[ibX];      
      ShowLimits33();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep(); 
  }
  else Beep();
}

*/
