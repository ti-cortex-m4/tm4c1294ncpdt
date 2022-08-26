/*------------------------------------------------------------------------------
KEY_ADDRESSES.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_records.h"
#include "../../digitals/digitals.h"
#include "../../flash/records.h"
#include "key_addresses.h"



//                                           0123456789ABCDEF
static char const       szAddresses[]     = "Адреса          ",
                        szMask[]          = "_________",
                        szSpace[]         = "         ";



static void Show(uchar  c)
{
  Clear();

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    sprintf(szHi+7,"%9lu",mpdwAddress1[c]);

    if (mpdwAddress2[c] == MAX_LONG)
      sprintf(szLo+7,"        -");
    else
      sprintf(szLo+7,"%9lu",mpdwAddress2[c]);
  }
  else
  {
    sprintf(szHi+7,"%9lu",mpdwAddress1[c]);
    sprintf(szLo+7,"*********");
  }

  sprintf(szLo,"%2u",c+1);
}



void    key_SetAddresses(void)
{
static uchar c;
static line  address;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Number();

      ShowHi(szAddresses);
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
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      ulong dw = GetLongLo(7,15);
      if (dw < 1000000000)
      {
        enKeyboard = KBD_POSTENTER;

        ibRecordCan = c;
        AddSysRecordReprogram(EVE_EDIT_ADDRESS20);

        mpdwAddress2[c] = dw;
        SaveCache(&chAddress2);

        memset(&address, 0, sizeof(address));
        sprintf(address.szLine, "%d", dw);

        mpphAsciiAddress[c] = address;
        SaveCache(&chAsciiAddress);

        AddSysRecordReprogram(EVE_EDIT_ADDRESS21);

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
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ulong dw = GetLongHi(7,15);
      if (dw < 1000000000)
      {
        enKeyboard = KBD_INPUT3;
        sprintf(szLo+7,szMask);

        ibRecordCan = c;
        AddSysRecordReprogram(EVE_EDIT_ADDRESS10);

        mpdwAddress1[c] = dw;
        SaveCache(&chAddress1);

        AddSysRecordReprogram(EVE_EDIT_ADDRESS11);
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTENTER;

      ibRecordCan = c;
      AddSysRecordReprogram(EVE_EDIT_ADDRESS20);

      mpdwAddress2[c] = MAX_LONG;
      SaveCache(&chAddress2);

      AddSysRecordReprogram(EVE_EDIT_ADDRESS21);

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
        sprintf(szHi+7,szMask);
        sprintf(szLo+7,szSpace);
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
      ShiftHi(7,15);
    }
    else
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(7,15);
    }
    else Beep();
  }
  else Beep();
}
