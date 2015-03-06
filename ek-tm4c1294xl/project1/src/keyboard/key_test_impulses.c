/*------------------------------------------------------------------------------
KEY_TEST_IMPULSES.H

 
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include       "inc/hw_gpio.h"
#include       "inc/hw_memmap.h"
#include       "inc/hw_sysctl.h"
#include       "inc/hw_types.h"



//                                         0123456789ABCDEF
static char const       szTestImp[]     = "Тест            ";



void    key_GetTestImpulses(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestImp);
      Clear();
    }
  }
}



void    auto_GetTestImpulses(void)
{
  if (enKeyboard == KBD_POSTENTER)
  { 
  }
}
