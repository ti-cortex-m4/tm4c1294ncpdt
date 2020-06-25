/*------------------------------------------------------------------------------
key_ascii_&address.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "ascii_address_wrapper.h"
#include "key_ascii_addresses.h"



//                                           0123456789ABCDEF
static char const       szAddresses[]     = "Адреса          ";



void    key_SetAsciiAddresses0(void)
{
static line  address;
static uchar idx;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      ShowHi(szAddresses);

      AsciiAddress_Init(&address);
      idx = 0;

      AsciiAddress_Show(&address);
    }
  }

  else if (bKey == 8)
  {
    AsciiAddress_Increment(&address);
    AsciiAddress_Show(&address);
  }

  else if (bKey == 0)
  {
    AsciiAddress_Decrement(&address);
    AsciiAddress_Show(&address);
  }

  else if (bKey == bKEY_MINUS)
  {
    if (idx > 1)
      AsciiAddress_Delete(&address, idx--);
    else
      { AsciiAddress_Init(&address); Beep(); }
    AsciiAddress_Show(&address);
  }

  else if (bKey == bKEY_POINT)
  {
    if (idx < 12)
      AsciiAddress_Enter(&address, ++idx);
    else
      Beep();
    AsciiAddress_Show(&address);
  }
  else Beep();
}
