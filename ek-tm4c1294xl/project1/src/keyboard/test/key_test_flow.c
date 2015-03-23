/*------------------------------------------------------------------------------
KEY_TEST_FLOW.H

 
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../keyboard.h"
#include        "../../display/display.h"



//                                         0123456789ABCDEF
static char const       szTestFlow[]    = "Транзит         ";



void    key_TestFlow(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szAnalysis2);
      Clear();
    }
  }
}


void    auto_TestFlow(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
    Hi(14, cbFlowDelay);

    if (ibPortFrom == 0)
    {
      Lo(0,  cbInFlow0);
      Lo(3,  iwInFlow0 / 0x100);
      Lo(5,  iwInFlow0 % 0x100);

      Lo(9,  cbOutFlow0);
      Lo(12, iwOutFlow0 / 0x100);
      Lo(14, iwOutFlow0 % 0x100);
    }

    if (ibPortFrom == 1)
    {
      Lo(0,  cbInFlow1);
      Lo(3,  iwInFlow1 / 0x100);
      Lo(5,  iwInFlow1 % 0x100);

      Lo(9,  cbOutFlow1);
      Lo(12, iwOutFlow1 / 0x100);
      Lo(14, iwOutFlow1 % 0x100);
    }
  }
}
