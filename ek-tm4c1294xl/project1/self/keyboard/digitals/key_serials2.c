/*------------------------------------------------------------------------------
KEY_SERIALS2,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/digitals.h"
#include "key_serials2.h"



//                                           0123456789ABCDEF
static char const       szSerials[]       = "Заводские номера",



static void Show(void)
{
//  if (GetDigitalDevice(c) == 0)
//    ShowFloat(GetCntCurrImp(c));
//  else
//  {
//    LoadCurrDigital(c);
//    ibPort = diCurr.ibPort;
//
//    if (LoadConnect(c) == 0) return;
//    Clear();
//
//    if (mpboEnblCan[c] == false)
//      ShowLo(szBlocked);
//    else
//    {
//      double2 db2 = ReadCntCurrCan(c);
//      (db2.fValid) ? ShowDouble(db2.dbValue) : Error();
//    }
//
//    SaveConnect();
//  }
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
      Show();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        Show();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS)
        c = 0;

      ibY = 0;
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (c > 0)
        c--;
      else
        c = bCANALS - 1;

      Show();
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
