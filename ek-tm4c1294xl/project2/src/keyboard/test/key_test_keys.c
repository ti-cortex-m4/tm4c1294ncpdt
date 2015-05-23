/*------------------------------------------------------------------------------
KEY_TEST_KEYS.H

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../health.h"
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


static void ShowKeys(uchar  i, uint  w)
{
  szLo[i] = (w == 0) ? '0' : '1';
}


void    auto_TestKeys(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
    ShowKeys(0,  HWREG(GPIO_PORTN_BASE + GPIO_O_DATA + 0x0004));
    ShowKeys(1,  HWREG(GPIO_PORTN_BASE + GPIO_O_DATA + 0x0008));
    ShowKeys(2,  HWREG(GPIO_PORTN_BASE + GPIO_O_DATA + 0x0010));
    ShowKeys(3,  HWREG(GPIO_PORTN_BASE + GPIO_O_DATA + 0x0020));
    ShowKeys(4,  HWREG(GPIO_PORTN_BASE + GPIO_O_DATA + 0x0040));
    ShowKeys(5,  HWREG(GPIO_PORTN_BASE + GPIO_O_DATA + 0x0080));

    ShowKeys(6,  HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0004));
    ShowKeys(7,  HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0008));
    ShowKeys(8,  HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0010));
    ShowKeys(9,  HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DATA + 0x0020));

    ShowKeys(11, HWREG(GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0004));
    ShowKeys(12, HWREG(GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0008));
    ShowKeys(13, HWREG(GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0010));
    ShowKeys(14, HWREG(GPIO_PORTQ_BASE + GPIO_O_DATA + 0x0020));
  }
}
