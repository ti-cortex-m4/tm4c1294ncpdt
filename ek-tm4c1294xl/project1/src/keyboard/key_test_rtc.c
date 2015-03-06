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



void    key_TestRTC(void)
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



static uchar ShowRTC(boolean  bo)
{
  switch (bo)
  {
    case TRUE:      return '+';
    case FALSE:     return '-';
    case UNDEFINED: return '?';
    default:        return '.';
  }
}



void    auto_TestRTC(void)
{
  if (enKeyboard == KBD_POSTENTER)
  { 
    szLo[0]= ShowRTC(boHealthLabelRTC);
    szLo[1]= ShowRTC(boHealthTimeRTC);
  }
}
