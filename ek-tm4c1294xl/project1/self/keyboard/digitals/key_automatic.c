/*------------------------------------------------------------------------------
KEY_AUTOMATIC!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../display/panel.h"
#include "../../serial/ports.h"
#include "../../serial/speeds_display.h"
#include "../../serial/modems.h"
#include "../../sensors/automatic1.h"
#include "../../sensors/automatic_w.h"
#include "../../sensors/sensor19/automatic19.h"
#include "../../sensors/sensor31/automatic31.h"
#include "../../sensors/sensor32/automatic32.h"
#include "../../sensors/sensor33/automatic33.h"
#include "../../sensors/sensor34/automatic34.h"
#include "../../sensors/sensor35/automatic35.h"
#include "../../sensors/sensor36/automatic36.h"
#include "../../sensors/sensor38/automatic38.h"
#include "../../sensors/sensor39/automatic39.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/digitals_display.h"
#include "../../impulses/factors.h"



//                                           0123456789ABCDEF
static char const       szAutomatic[]     = "Заполнение      ",
                        szCana1s[]        = "Каналы:         ",
                        szCana1FromMask[] = " от: __",
                        szCana1ToMask[]   = " до: __";

static uchar            ibXmin, ibXmax;



void    Automatic(uchar  ibMin, uchar  ibMax)
{
uchar   i;

      enKeyboard = KBD_POSTENTER;

      ShowHi(szAutomatic);
      Clear(); DelayInf();

      for (ibPort=0; ibPort<bPORTS; ibPort++)
      {
        ShowPortDelayLo(ibPort);
        DelayInf(); fKey = 0;
      }

      Clear();
      InitConnectKey();

      ibX = 0;

      for (i=ibMin; i<ibMax; i++)
      {
        if (GetDigitalDevice(i) == 0) continue;

        uchar bRes = 0;

        LoadCurrDigital(i);
        ibPort = diCurr.ibPort;

        if (GetDigitalDevice(i) != 0)
        {
          if (StreamPortCan(GetDigitalPort(i),i) == 0)
          { bRes = 0xEE; break; }
        }

        ShowCanalNumber(i);
        ShowProgress(12,(ulong)100*i/(bCANALS-1)); DelayInf();

        if (LoadConnect(i) == 0) break;
        Clear();

        if (mpboEnblCan[i] == false)
        {
          ShowLo(szBlocked);
          DelayMsg();
        }
        else switch (diCurr.bDevice)
        {
#ifndef SKIP_A
          case 15:
          case 1:  if (AutomaticA() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_B
          case 12: if (AutomaticJ(i) != 1) bRes = 0xEE; break;

          case 8:
          case 2:  if (AutomaticB(i) != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_C
          case 3:  if (AutomaticC(i) != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_D
          case 4:  if (AutomaticD() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_E
          case 7:
          case 5:  if (AutomaticE() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_F
          case 6:  if (AutomaticF() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_G
          case 9:  if (AutomaticG() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_H
          case 10: if (AutomaticH() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_I
          case 11: if (AutomaticI() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_K
          case 14:
          case 13: if (AutomaticK() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_L
          case 17:
          case 16: if (AutomaticK() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_M
          case 18: if (AutomaticM() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_N
          case 19: if (AutomaticN() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_O
          case 20: if (AutomaticO() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_P
          case 21: if (AutomaticP(i) != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_Q
          case 22: if (AutomaticK() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_R
          case 23: if (AutomaticR() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_S
          case 24: if (AutomaticS() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_T
          case 25: if (AutomaticT() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_U
          case 28:
          case 26: if (AutomaticK() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_V
          case 27: if (AutomaticV() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_W
          case 29:
          case 30: if (AutomaticW() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_31
          case 31: if (Automatic31() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_32
          case 32: if (Automatic32() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_33
          case 33: if (Automatic33() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_34
          case 34: if (Automatic34() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_35
          case 35: if (Automatic35() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_36
          case 36:
          case 37: if (Automatic36() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_38
          case 38: if (Automatic38() != 1) bRes = 0xEE; break;
          case 39: if (Automatic39() != 1) bRes = 0xEE; break;
#endif

#ifndef SKIP_40
          case 40: if (Automatic40() != 1) bRes = 0xEE; break;
#endif
        }

        SaveConnect();

        if (bRes == 0xEE)
        {
          ibX++;
          Error(); Beep(); DelayMsg();
        }

        if (fKey == true) bRes = 0xFF;
        fKey = 0;

        if (bRes == 0xFF) break;
#ifdef NO_DISPLAY
        RunPanel();
#endif
      }

      ShowHi(szAutomatic);
      if (ibX != 0) { Clear(); sprintf(szLo+3, "ошибок: %-2u", ibX); LongBeep(); DelayMsg(); }  else OK();

      DelayMsg();
      KeyBreakConnect();

      SaveFactors();
}



void    key_Automatic1(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      Automatic(0,bCANALS);
    }
  }
}


void    key_Automatic2(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      ShowHi(szAutomatic);
      Clear(); DelayInf();

      ShowHi(szCana1s);
      strcpy(szLo+0,szCana1FromMask);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibXmin = GetCharLo(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCana1ToMask);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetCharLo(13,14) - 1;
      if ((ibXmax < bCANALS) && (ibXmax >= ibXmin))
      {
        Automatic(ibXmin,ibXmax+1);
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
    else Beep();
  }
  else Beep();
}
