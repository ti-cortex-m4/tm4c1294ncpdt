/*------------------------------------------------------------------------------
KEY_LIMITS32.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_limits.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/limits.h"



//                                           0123456789ABCDEF
static char const       szLimits32[]        = "Нижняя граница  ",
                        szCanals32[]        = "Каналы:         ",
                        szMaskLimits32[]    = "    ____        ",
                        szCanalFromMask32[] = " от: __",
                        szCanalToMask32[]   = " до: __";

static uchar            ibXmin, ibXmax;



void    key_SetLimits32(void)
{ 
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boUseBounds == TRUE)
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
      ibXmin = GetCharLo(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalToMask32);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetCharLo(13,14) - 1;
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
      uint w;
      if ((w = GetIntLo(4,7)) < wHOURS)
      {
        enKeyboard = KBD_POSTENTER;

        for (ibX=ibXmin; ibX<=ibXmax; ibX++) mpcwStartRelCan[ibX] = w;
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
