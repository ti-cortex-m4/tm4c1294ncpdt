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
    Hi(12, cwPageErase / 0x100);
    Hi(14, cwPageErase % 0x100);

    szLo[5] = 'R';
    Lo(6,  cwPageRead / 0x100);
    Lo(8,  cwPageRead % 0x100);

    szLo[11] = 'W';
    Lo(12, cwPageWrite / 0x100);
    Lo(14, cwPageWrite % 0x100);
  }
}
