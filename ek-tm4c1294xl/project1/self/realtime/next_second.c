/*------------------------------------------------------------------------------
NEXT_SECOND!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_profile.h"
#include "../sensors/sensor21/device_p.h"
#include "../digitals/wait_query.h"
#include "../digitals/profile/profile_run.h"
#include "../digitals/current/current_run.h"
#include "../digitals/schedule/ctrl_hours.h"
#include "../digitals/phones2/phones2_z.h"
#include "period30.h"
#include "realtime.h"



void    NextSecond(void)
{
  Realtime1.cdwSeconds++;

  if ((fActive == true) && (enGlobal != GLB_PROGRAM))
  {
    cwHouLength++;
    if ((fProfile == 1) && (cbWaitQuery == 0))
    {
      if ((tiCurr.bMinute % 30)*60 + tiCurr.bSecond >= bTimeoutProfile)
      {
        boManualProfile = false;
        fProfile = 0;
        RunProfile((boControlTime == true) && (ControlTime() == 1));
      }
    }
  }

  if ((fActive == true) && (enGlobal != GLB_PROGRAM))
  {
    if ((fCurrent == 1) && (cbWaitQuery == 0))
    {
      if ((tiCurr.bMinute % 3)*60 + tiCurr.bSecond >= bTimeoutCurrent)
      {
        RunCurrent();
      }
    }
  }

  if ((fActive == true) && (enGlobal != GLB_PROGRAM))
  {
    EverySecondP();
  }

  if ((fActive == 1) && (enGlobal != GLB_PROGRAM))
  {
    EverySecondPhones2();
  }

  NextSecPeriod30();
}
