/*------------------------------------------------------------------------------
KEY_TEST_KEYS.H

 
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../health.h"
#include       "inc/hw_gpio.h"
#include       "inc/hw_memmap.h"
#include       "inc/hw_sysctl.h"
#include       "inc/hw_types.h"



//                                         0123456789ABCDEF
static char const       szTestKeys[]    = "Тест клавиатуры ";



void    key_TestKeys(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestKeys);
      Clear();
    }
  }
}



void    auto_TestKeys(void)
{
  if (enKeyboard == KBD_POSTENTER)
  { 
  }
}
