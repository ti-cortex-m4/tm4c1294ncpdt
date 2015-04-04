/*------------------------------------------------------------------------------
_DIVIDER.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "beep.h"
#include        "timer0.h"
#include        "display.h"
#include        "keyboard.h"
#include        "programs.h"
#include        "access.h"
#include        "energy.h"
#include        "engine.h"



//                                         0123456789ABCDEF
uchar           code    szDivider[]     = "К пропрорц.     ",
                        szMaskDivider[] = "________ ___";
                      



void    ShowDivider(void)
{
  reBuffA = mpreParamDiv[iwA];
  sprintf(szLo,"%12.3f", reBuffA);

  sprintf(szLo+13,"%3u",iwA+1);
}



void    key_SetDivider(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Param();

      ShowHi(szDivider);
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      iwA = 0;
      ShowDivider();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((iwA = GetInt(10,12) - 1) < wPARAMS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowDivider();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++iwA >= wPARAMS) iwA = 0;

      ShowDivider();
    }
    else if ((enKeyboard == KBD_POSTINPUT2) || (enKeyboard == KBD_POSTINPUT3))
    {      
      reBuffA = *PGetReal(0,7) + *PGetReal(9,11)/1000;

      if (reBuffA >= 0)
      {
        enKeyboard = KBD_POSTENTER;

        mpreParamDiv[iwA] = reBuffA;
      }
      else Beep();

      if (enKeyboard == KBD_POSTENTER)
      {
        if (++iwA >= wPARAMS) iwA = 0;

        ShowDivider();
      }
      else 
      {
        enKeyboard = KBD_INPUT2;
        LongBeep();

        ShowLo(szMaskDivider);
      }
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (iwA > 0) iwA--; else iwA = wPARAMS-1;

      ShowDivider();
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT3;
      szLo[8] = '.';
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT2;
      ShowLo(szMaskDivider);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,12);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(0,7);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(9,11);
    }
  }
  else Beep();
}

*/
