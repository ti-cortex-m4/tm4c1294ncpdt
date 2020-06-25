/*------------------------------------------------------------------------------
key_ascii_addresses.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_records.h"
#include "../../digitals/digitals.h"
// #include "../../flash/records.h"
#include "api_ascii_addresses.h"
#include "key_ascii_addresses.h"



//                                           0123456789ABCDEF
static char const       szAddresses[]     = "Адреса          ",
                        szMask9[]         = "_________",
                        szSpace9[]        = "         ",
                        szMask12[]        = "____________",
                        szSpace12[]       = "            ";



static void Show(uchar  c, line  *address)
{
  Clear();

  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    sprintf(szHi+7,"%9lu",mpdwAddress1[c]);
    AsciiAddress_Show(&address);
  }
  else
  {
    sprintf(szHi+7,"%9lu",mpdwAddress1[c]);
    sprintf(szLo+7,"*********");
  }

  sprintf(szLo,"%2u",c+1);
}



void    key_SetAsciiAddresses(void)
{
static uchar c;
static line  address;
static uchar idx;

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
      Show(c, &address);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((c = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        Show(c, &address);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++c >= bCANALS) c = 0;
      Show(c, &address);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
        enKeyboard = KBD_POSTENTER;

        mpphAsciiAddress2[c] = address;
        SaveCache(&chAsciiAddress);

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
      Show(c, &address);
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ulong dw = GetLongHi(7,15);
      if (dw < 1000000000)
      {
        enKeyboard = KBD_INPUT3;
        sprintf(szLo+7,szMask9);

        ibRecordCan = c;
        AddSysRecordReprogram(EVE_EDIT_ADDRESS10);

        mpdwAddress1[c] = dw;
        SaveCache(&chAddress1);

        AddSysRecordReprogram(EVE_EDIT_ADDRESS11);
      }
      else Beep();
    }
    else if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      if (idx < 12)
        AsciiAddress_Enter(&address, ++idx);
      else
        Beep();
      AsciiAddress_Show(&address);            
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      if (idx > 1)
        AsciiAddress_Delete(&address, idx--);
      else
        { AsciiAddress_Init(&address); Beep(); }
      AsciiAddress_Show(&address);
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
        sprintf(szHi+7,szMask9);
        sprintf(szLo+7,szSpace9);
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

      if (bKey == 8)
      {
        AsciiAddress_Increment(&address);
        AsciiAddress_Show(&address);
      }
      else if (bKey == 0)
      {
        AsciiAddress_Decrement(&address);
        AsciiAddress_Show(&address);
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
