/*------------------------------------------------------------------------------
KEY_SERIALS,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/digitals.h"
#include "key_ыукшфды.h"



//                                           0123456789ABCDEF
static char const       szSerials[]       = "Заводские номера",
                        szMask[]          = "_________",
                        szSpace[]         = "         ";



static void Show(uchar  c)
{
  Clear();

  sprintf(szLo+7,"%9lu",mdwSerialValues[c]);
  sprintf(szLo,"%2u",c+1);
}



void    key_SetSerials(void)
{
static uchar c;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Canal();

      ShowHi(szSerials);
    }
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      c = 0;
      Show(c);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Show(c);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;
      Show(c);
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ulong dw = GetLongLo(7,15);
      if (dw < 1000000000)
      {
        enKeyboard = KBD_POSTENTER;

        mdwSerialValues[c] = dw;
        SaveCache(&chSerialValues);

        if (++c >= bCANALS) c = 0;
        Show(c);
      }
      else Beep();
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


  else if (bKey == bKEY_MINUS)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTENTER;

//      mpdwAddress2[c] = MAX_LONG;
//      SaveCache(&chAddress2);

      if (++c >= bCANALS) c = 0;
      Show(c);
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
      {
        enKeyboard = KBD_INPUT2;
        sprintf(szLo+7,szMask);
      }
      else Beep();
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
      ShiftLo(7,15);
    }
    else Beep();
  }
  else Beep();
}
