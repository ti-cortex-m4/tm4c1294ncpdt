/*------------------------------------------------------------------------------
KEYBOARD_AUTO.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/programs.h"
#include "../digitals/digitals.h"
#include "../impulses/impulses.h"
#include "keyboard.h"
#include "time/key_timedate.h"
#include "impulses/key_single.h"
#include "impulses/key_single2.h"
#include "impulses/key_oldprogram73.h"
#include "impulses/key_oldprogram74.h"
#include "test/key_test_response.h"
#include "test/key_test_flow.h"
#include "test/key_test_ports_io.h"
#include "test/key_test_uni.h"
#include "test/key_test_flash.h"
#include "test/key_test_impulses.h"
#include "test/key_test_keys.h"
#include "test/key_test_rtc.h"



void    Keyboard_Auto(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    switch (wProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bTEST_IMPULSES:      auto_TestImpulses();    break;
      case bTEST_KEYS:          auto_TestKeys();        break;
      case bTEST_RTC:           auto_TestRTC();         break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (wProgram)
    {
      case bGET_CORRECT_TIME:
      case bGET_CURRTIME:       auto_GetCurrTime();     break;
      case bGET_CURRDATE:       auto_GetCurrDate();     break;

      case bTEST_IMPULSES:      auto_TestImpulses();    break;
      case bTEST_KEYS:          auto_TestKeys();        break;
      case bTEST_RTC:           auto_TestRTC();         break;
    }

    // обновление показаний с каждым импульсом
    if (fOnImpulse == 1)
    {
      fOnImpulse = 0;
    }

    // обновление показаний с частотой 1 √ц
    if (fOnSecond == 1)
    {
      fOnSecond = 0;
    }
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (wProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bTEST_IMPULSES:      auto_TestImpulses();    break;
      case bTEST_KEYS:          auto_TestKeys();        break;
      case bTEST_RTC:           auto_TestRTC();         break;
    }
  }
}
