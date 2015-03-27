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
#include        "programs.h"
#include        "display.h"



//                                           0123456789ABCDEF
message          code   szLimits32        = "Нижняя граница  ",
                        szCanals32        = "Каналы:         ",
                        szMaskLimits32    = "    ____        ",
                        szCanalFromMask32 = " от: __",
                        szCanalToMask32   = " до: __";



void    key_SetLimits32(void)
{ 
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boStartCan == boTrue)
      {
        enKeyboard = KBD_INPUT1;

        ShowHi(szLimits32);
        Clear(); DelayInf();

        ShowHi(szCanals32);
        strcpy(szLo+0,szCanalFromMask32);
      }
      else BlockProgram(bSET_LIMITS30);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibXmin = GetChar(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalToMask32);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetChar(13,14) - 1;
      if ((ibXmax < bCANALS) && (ibXmax >= ibXmin))
      {
        enKeyboard = KBD_INPUT3;

        ShowHi(szLimits32);
        ShowLo(szMaskLimits32);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if ((iwA = GetInt(4,7)) < wHOURS)
      {
        enKeyboard = KBD_POSTENTER;

        for (ibX=ibXmin; ibX<=ibXmax; ibX++) mpcwStartRelCan[ibX] = iwA;
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
