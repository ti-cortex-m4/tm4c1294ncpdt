/*------------------------------------------------------------------------------
KEYBOARD_KEY.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/programs.h"
#include "keyboard.h"
#include "key_speeds.h"
#include "time/key_timedate.h"
#include "key_password.h"
#include "key_logical.h"
#include "key_private.h"
#include "key_start.h"
#include "key_version.h"
#include "key_groups.h"
#include "key_factors.h"
#include "key_delays.h"
#include "key_reset.h"
#include "test/key_test_direct.h"
#include "test/key_test_response.h"
#include "test/key_test_flow.h"
#include "test/key_test_ports_io.h"
#include "test/key_test_uni.h"
#include "test/key_test_flash.h"
#include "test/key_test_impulses.h"
#include "test/key_test_keys.h"
#include "test/key_test_rtc.h"



void    Keyboard_Key(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    switch (wProgram)
    {
      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;

      default:                  NoProgram();            break;
    }
  }

  else if (enGlobal == GLB_WORK)
  {
    switch (wProgram)
    {
      case bGET_CURRTIME:       key_SetCurrTime();      break;
      case bGET_CURRDATE:       key_SetCurrDate();      break;
      default:                  NoProgram();            break;
    }
  }

  else if (enGlobal == GLB_REPROGRAM)
  {
    switch (wProgram)
    {
      case bSET_CURRTIME:       key_SetCurrTime();      break;
      case bSET_CURRDATE:       key_SetCurrDate();      break;

      default:                  NoProgram();            break;
    }
  }
}
