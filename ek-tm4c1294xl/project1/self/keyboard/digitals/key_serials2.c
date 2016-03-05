/*------------------------------------------------------------------------------
KEY_SERIALS2,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/serials_read.h"
#include "../../serial/ports.h"
#include "../../serial/modems.h"
#include "key_serials2.h"



//                                           0123456789ABCDEF
static char const       szSerials[]       = "Заводские номера";



static void ShowValue(ulong  dw)
{
  sprintf(szLo+4,"%9lu",dw);
}


static void Show(uchar  c)
{
  Clear();

  if (GetDigitalDevice(c) == 0)
  {
    ShowValue(wPrivate);
    szLo[0] = '*';
  }
  else
  {
    LoadCurrDigital(c);
    ibPort = diCurr.ibPort;

    if (LoadConnect(c) == 0) return;
    Clear();

    if (mpboEnblCan[c] == false)
      ShowLo(szBlocked);
    else
    {
      ulong2 dw2 = ReadSerialCan(c);
      (dw2.fValid) ? ShowValue(dw2.dwValue) : Error();
    }

    SaveConnect();
  }

  sprintf(szLo+14,"%2u",c+1);
}



void    key_SetSerials2(void)
{
static uchar c;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

      InitConnectKey();

      ShowHi(szSerials);
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      c = 0;
      Show(c);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        Show(c);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;
      Show(c);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (c > 0) c--; else c = bCANALS-1;
      Show(c);
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
