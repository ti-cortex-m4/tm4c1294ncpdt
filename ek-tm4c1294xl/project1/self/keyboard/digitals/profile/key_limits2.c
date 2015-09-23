/*------------------------------------------------------------------------------
KEY_LIMITS2!C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_limits.h"
#include "../../keyboard.h"
#include "../../../display/display.h"
#include "../../../digitals/limits.h"



//                                           0123456789ABCDEF
static char const       szLimits[]        = "Верхняя граница ",
                        szCanals[]        = "Каналы:         ",
                        szMaskLimits[]    = "    ____        ",
                        szCanalFromMask[] = " от: __",
                        szCanalToMask[]   = " до: __";

static uchar            ibXmin, ibXmax;



void    key_SetLimits2(void)
{ 
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      ShowHi(szLimits);
      Clear(); DelayInf();

      ShowHi(szCanals);
      strcpy(szLo+0,szCanalFromMask);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibXmin = GetCharLo(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalToMask);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetCharLo(13,14) - 1;
      if ((ibXmax < bCANALS) && (ibXmax >= ibXmin))
      {
        enKeyboard = KBD_INPUT3;

        ShowHi(szLimits);
        ShowLo(szMaskLimits);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      uint w;
      if ((w = GetIntLo(4,7)) < wHOURS)
      {
        enKeyboard = KBD_POSTENTER;

        for (ibX=ibXmin; ibX<=ibXmax; ibX++) mpcwStopCan[ibX] = w;
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

      uint w;
      if ((w = GetIntLo(4,7)) < wHOURS)
        sprintf(szLo+8,":%02u",(uchar)(w/48 + 1));
      else
        sprintf(szLo+8," ? ");
    }
    else Beep(); 
  }
  else Beep();
}
