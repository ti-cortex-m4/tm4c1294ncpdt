/*------------------------------------------------------------------------------
key_ascii_&address.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "ascii_address.h"
#include "key_ascii_addresses.h"



//                                           0123456789ABCDEF
static char const       szAddresses[]     = "Адреса          ";

static line             address;



void    key_SetAsciiAddresses(void)
{
static uchar i;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      ShowHi(szAddresses);

      AsciiAddress_Init(&address);
      i = 0;

      AsciiAddress_Show(&address);
    }
  }

  else if (bKey == 2)
  {
    AsciiAddress_Increment(&address);
    AsciiAddress_Show(&address);
  }

  else if (bKey == 8)
  {
    AsciiAddress_Decrement(&address);
    AsciiAddress_Show(&address);
  }

  else if (bKey == bKEY_MINUS)
  {
    i--;
    AsciiAddress_Delete(&address);
    AsciiAddress_Show(&address);
  }

  else if (bKey == bKEY_POINT)
  {
    AsciiAddress_Enter(&address, ++i);
    AsciiAddress_Show(&address);
  }
  else Beep();
}
