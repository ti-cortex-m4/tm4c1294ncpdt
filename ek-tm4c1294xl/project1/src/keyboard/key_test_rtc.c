/*------------------------------------------------------------------------------
KEY_TEST_RTC.H

 
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
static char const       szTestRTC[]     = "Тест часов      ";



void    key_GetTestRTC(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestRTC);
      Clear();
    }
  }
}



uchar   ShowTestRTC(boolean  bo)
{
  switch (bo)
  {
    case TRUE:      return '+';
    case FALSE:     return '-';
    case UNDEFINED: return '?';
    default:        return '.';
  }
}



void    auto_GetTestRTC(void)
{
  if (enKeyboard == KBD_POSTENTER)
  { 
    szLo[0]= ShowTestRTC(boHealthLabelRTC);
    szLo[1]= ShowTestRTC(boHealthTimeRTC);
  }
}
