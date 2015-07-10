/*------------------------------------------------------------------------------
KEY_TEST_FLOW.H

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_flash.h"
#include "../keyboard.h"
#include "../../display/display.h"



//                                         0123456789ABCDEF
static char const       szTestFlash[]   = "AT45            ";



void    key_TestFlash(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestFlash);
      Clear();
    }
  }
}


void    auto_TestFlash(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
  	szHi[11] = 'E';
    Hi(12, cdwPageErase / 0x100);
    Hi(14, cdwPageErase % 0x100);

    szLo[5] = 'R';
    Lo(6,  cdwPageRead / 0x100);
    Lo(8,  cdwPageRead % 0x100);

    szLo[11] = 'W';
    Lo(12, cdwPageWrite / 0x100);
    Lo(14, cdwPageWrite % 0x100);
  }
}
