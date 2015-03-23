/*------------------------------------------------------------------------------
KEY_TEST_UNI.H

 
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_uni.h"
#include        "../keyboard.h"
#include        "../../display/display.h"



//                                         0123456789ABCDEF
static char const       szTestUni[]     = "“‡ÈÏ‡ÛÚ˚ ”œ»Œ   ";



void    key_TestUni(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestUni);
      Clear();

      Lo(14, bMaxDelayUni);
    }
  }
}


void    auto_TestUni(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
    Lo(0, mpbDelayUni[0]);
    Lo(3, mpbDelayUni[1]);
    Lo(6, mpbDelayUni[2]);
    Lo(9, mpbDelayUni[3]);
  }
}
