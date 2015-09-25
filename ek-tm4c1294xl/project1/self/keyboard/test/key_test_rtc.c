/*------------------------------------------------------------------------------
KEY_TEST_RTC.H

Тест часов
------------------------------------------------------------------------------*/

#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_realtime.h"
#include "../../time/rtc.h"
#include "key_test_rtc.h"



//                                         0123456789ABCDEF
static char const       szMessageHi[]   = "Тест RTC        ",
                        szMessageLo[]   = "метка    время  ";



void    key_TestRTC(void)
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



static uchar Show(bool  f)
{
  switch (f)
  {
    case true:  return '+';
    case false: return '-';
    default:    return '?';
  }
}



void    auto_TestRTC(void)
{
  if (enKeyboard == KBD_POSTENTER)
  {
    szLo[6]  = Show(fHealthLabelRTC);
    szLo[15] = Show(fHealthTimeRTC);
  }
}
