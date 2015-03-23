/*------------------------------------------------------------------------------
KEY_TEST_PORTS_IO.H

 
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../serial/ports.h"
#include        "../../isr/serial2.h"
#include        "../../isr/serial3.h"



//                                          0123456789ABCDEF
static char const       szTestPortsIO1[] = "¬вод/вывод      ",
                        szTestPortsIO2[] = "  3:     4:     ";



void    key_TestPortsIO(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestPortsIO1);
      ShowLo(szTestPortsIO2);
    }
    else Beep();
  }
  else if (bKey == 3)
  {
    if (enGlobal != GLB_WORK)
      InputMode2();
    else
      Beep();
  }
  else if (bKey == 4)
  {
    if (enGlobal != GLB_WORK)
      InputMode3();
    else
      Beep();
  }
  else Beep();
}


void    auto_TestPortsIO(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
    if ((bPortsStatus & 0x01) == 0) {
      szLo[4] = 'i';
      szLo[5] = 'n';
      szLo[6] = ' ';
    }
    else
    {
      szLo[4] = 'o';
      szLo[5] = 'u';
      szLo[6] = 't';
    }

    if ((bPortsStatus & 0x02) == 0) {
      szLo[11] = 'i';
      szLo[12] = 'n';
      szLo[13] = ' ';
    }
    else
    {
      szLo[11] = 'o';
      szLo[12] = 'u';
      szLo[13] = 't';
    }
  }
}
