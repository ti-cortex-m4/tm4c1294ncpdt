/*------------------------------------------------------------------------------
_LIMITS2.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "delay.h"
#include        "beep.h"
#include        "timer0.h"
#include        "keyboard.h"
#include        "display.h"



//                                         0123456789ABCDEF
message          code   szLimits2       = "Верхняя граница ",
                        szCanals        = "Каналы:         ",
                        szMaskLimits2   = "    ____        ",
                        szCanalFromMask = " от: __",
                        szCanalToMask   = " до: __";



void    key_SetLimits2(void)
{ 
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      ShowHi(szLimits2);
      Clear(); DelayInf();

      ShowHi(szCanals);
      strcpy(szLo+0,szCanalFromMask);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibXmin = GetChar(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalToMask);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetChar(13,14) - 1;
      if ((ibXmax < bCANALS) && (ibXmax >= ibXmin))
      {
        enKeyboard = KBD_INPUT3;

        ShowHi(szLimits2);
        ShowLo(szMaskLimits2);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if ((iwA = GetInt(4,7)) < wHOURS)
      {
        enKeyboard = KBD_POSTENTER;

        for (ibX=ibXmin; ibX<=ibXmax; ibX++) mpcwStopCan[ibX] = iwA;
        OK();
      }
      else Beep();
    }
    else Beep();
  }



  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(5,6);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(13,14);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(4,7);

      if ((iwA = GetInt(4,7)) < wHOURS)
        sprintf(szLo+8,":%02bu",(uchar)(iwA/48 + 1));
      else
        sprintf(szLo+8," ? ");
    }
    else Beep(); 
  }
  else Beep();
}

*/
