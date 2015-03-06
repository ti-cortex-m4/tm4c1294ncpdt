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



//                                          0123456789ABCDEF
static char const       szTestImpulses[] = "Тест импульсов  ";



void    key_TestImpulses(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestImpulses);
      Clear();
    }
  }
}


static void ShowImpulses(uchar  i, uint  w)
{

}


void    auto_TestImpulses(void)
{
  if (enKeyboard == KBD_POSTENTER)
  { 
    ShowImpulses(0,  HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0004));
    ShowImpulses(1,  HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0008));
    ShowImpulses(2,  HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0010));
    ShowImpulses(3,  HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0020));
    ShowImpulses(4,  HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0040));
    ShowImpulses(5,  HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0080));
    ShowImpulses(6,  HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0100));
    ShowImpulses(7,  HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x0200));

    ShowImpulses(8,  HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0004));
    ShowImpulses(9,  HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0008));
    ShowImpulses(10, HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0010));
    ShowImpulses(11, HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0020));
    ShowImpulses(12, HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0040));
    ShowImpulses(13, HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0080));
    ShowImpulses(14, HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0100));
    ShowImpulses(15, HWREG(GPIO_PORTM_BASE + GPIO_O_DATA + 0x0200));
  }
}
