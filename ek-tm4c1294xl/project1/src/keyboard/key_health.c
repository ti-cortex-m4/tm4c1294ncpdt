/*------------------------------------------------------------------------------
KEY_HEALTH.H

 
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
static char const       szHealth[]      = "Запросы         ";



void    key_GetHealth(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szHealth);
      Clear();
    }
  }
}



uchar   GetHealth(boolean  bo)
{
  switch (bo)
  {
    case TRUE:      return '+';
    case FALSE:     return '-';
    case UNDEFINED: return '?';
    default:        return '.';
  }
}



void    auto_GetHealth(void)
{
  if (enKeyboard == KBD_POSTENTER)
  { 
    szLo[0]= GetHealth(boHealthLabelRTC);
	  szLo[1]= GetHealth(boHealthTimeRTC);

	  Lo(5, HWREG((GPIO_PORTK_BASE + GPIO_O_DATA + 0x0004)));
  }
}
