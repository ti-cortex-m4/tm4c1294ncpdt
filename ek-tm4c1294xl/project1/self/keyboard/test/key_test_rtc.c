/*------------------------------------------------------------------------------
KEY_TEST_RTC.H

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../hardware/power_off.h"
#include "../../health.h"
#include       "inc/hw_gpio.h"
#include       "inc/hw_memmap.h"
#include       "inc/hw_sysctl.h"
#include       "inc/hw_types.h"



//                                         0123456789ABCDEF
static char const       szTestRTC1[]    = "Тест часов      ",
                        szTestRTC2[]    = "метка    время  ";



void    key_TestRTC(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestRTC1);
      ShowLo(szTestRTC2);
    }
  }
}



static uchar ShowRTC(bool  bo)
{
  switch (bo)
  {
    case true:      return '+';
    case false:     return '-';
    case UNDEFINED: return '?';
    default:        return ' ';
  }
}



void    auto_TestRTC(void)
{
  if (enKeyboard == KBD_POSTENTER)
  { 
    szLo[6]  = ShowRTC(boHealthLabelRTC);
    szLo[15] = ShowRTC(boHealthTimeRTC);
    szHi[15] = IsPowerOff() ? '+' : '-';
  }
}
