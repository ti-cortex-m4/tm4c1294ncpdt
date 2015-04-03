/*------------------------------------------------------------------------------
NEXT_SECOND.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_profile.h"
#include        "../digitals/wait_query.h"
#include        "../digitals/profile/profile_run.h"
#include        "../digitals/schedule/ctrl_hours.h"
#include        "realtime.h"



void    NextSecond(void)
{
  cdwSeconds++;

  if ((fActive == 1) && (enGlobal != GLB_PROGRAM))
  {
    cwHouLength++;
    if ((fProfile == 1) && (cbWaitQuery == 0))
    {
      if ((tiCurr.bMinute % 30)*60 + tiCurr.bSecond >= bTimeoutProfile)
      {
        boManualProfile = FALSE;
        fProfile = 0;
        RunProfile((boControlTime == TRUE) && (ControlTime() == 1));
      }
    }
  }
}
