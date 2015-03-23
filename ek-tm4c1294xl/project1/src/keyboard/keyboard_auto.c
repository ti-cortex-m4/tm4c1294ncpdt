/*------------------------------------------------------------------------------
KEYBOARD_AUTO.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../include/programs.h"
#include        "../digitals/digitals.h"
#include        "../impulses/impulses.h"
#include        "keyboard.h"
#include        "key_timedate.h"
#include        "impulses/key_single.h"
#include        "impulses/key_single2.h"
#include        "impulses/key_oldprogram73.h"
#include        "impulses/key_oldprogram74.h"
#include        "test/key_test_response.h"
#include        "test/key_test_flow.h"
#include        "test/key_test_ports_io.h"
#include        "test/key_test_uni.h"
#include        "test/key_test_impulses.h"
#include        "test/key_test_keys.h"
#include        "test/key_test_rtc.h"



void    Keyboard_Auto(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bTEST_RESPONSE:      auto_TestResponse();    break;
      case bTEST_FLOW:          auto_TestFlow();        break;
      case bTEST_PORTS_IO:      auto_TestPortsIO();     break;
      case bTEST_UNI:           auto_TestUni();         break;

      case bTEST_IMPULSES:      auto_TestImpulses();    break;
      case bTEST_KEYS:          auto_TestKeys();        break;
      case bTEST_RTC:           auto_TestRTC();         break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (bProgram)
    {
      case bGET_CURRTIME:       auto_GetCurrTime();     break;
      case bGET_CURRDATE:       auto_GetCurrDate();     break;

      case bTEST_RESPONSE:      auto_TestResponse();    break;
      case bTEST_FLOW:          auto_TestFlow();        break;
      case bTEST_PORTS_IO:      auto_TestPortsIO();     break;
      case bTEST_UNI:           auto_TestUni();         break;

      case bTEST_IMPULSES:      auto_TestImpulses();    break;
      case bTEST_KEYS:          auto_TestKeys();        break;
      case bTEST_RTC:           auto_TestRTC();         break;
    }

    // обновление показаний с каждым импульсом
    if (fOnImpulse == 1)
    {
      fOnImpulse = 0;
      switch (bProgram)
      {
        case bGET_CNTCURR_10:
        case bGET_CNTCURR_110:      if (GetDigitalDevice(ibX) == 0)
                                    auto_GetSingle();   break;

        case bGET_IMPCANCURRMNT:    auto_GetSingle();   break;
      }
    }

    // обновление показаний с частотой 1 √ц
    if (fOnSecond == 1)
    {
      fOnSecond = 0;
      switch (bProgram)
      {
        case bGET_POWGRPPREVHOU:
        case bGET_POWGRPCURRHOU:

        case bGET_POWGRPCURRMNT:    auto_GetSingle();   break;

        case bGET_POWCANPREVHOU:
        case bGET_POWCANCURRHOU:

        case bGET_POWCANCURRMNT:    auto_GetSingle2();  break;

        case bGET_PROGRAM73:   auto_GetOldProgram73();  break;
        case bGET_PROGRAM74:   auto_GetOldProgram74();  break;
      }
    }
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (bProgram)
    {
      case bSET_CURRDATE:       auto_GetCurrDate();     break;
      case bSET_CURRTIME:       auto_GetCurrTime();     break;

      case bTEST_RESPONSE:      auto_TestResponse();    break;
      case bTEST_FLOW:          auto_TestFlow();        break;
      case bTEST_PORTS_IO:      auto_TestPortsIO();     break;
      case bTEST_UNI:           auto_TestUni();         break;

      case bTEST_IMPULSES:      auto_TestImpulses();    break;
      case bTEST_KEYS:          auto_TestKeys();        break;
      case bTEST_RTC:           auto_TestRTC();         break;
    }
  }
}
