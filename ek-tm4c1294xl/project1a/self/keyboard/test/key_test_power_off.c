/*------------------------------------------------------------------------------
KEY_TEST_POWER_OFF.H

Тест датчика напряжения
------------------------------------------------------------------------------*/

#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "../../main.h"
#include "../../console.h"
#include "../../hardware/power_off.h"
#include "key_test_power_off.h"



//                                         0123456789ABCDEF
static char const       szMessageHi[]   = "Тест датчика    ",
                        szMessageLo[]   = "напряжения      ";



void    key_TestPowerOff(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szMessageHi);
      ShowLo(szMessageLo);
    }
  }
}



void    auto_TestPowerOff(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
    szLo[13] = IsPowerOff() ? '-' : '+';
  }
}
