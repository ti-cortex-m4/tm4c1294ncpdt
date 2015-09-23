/*------------------------------------------------------------------------------
NEXT_MINUTE1.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "realtime.h"
#include "throughput.h"
#include "../keyboard/time/key_timedate.h"



void    NextMinute1(void)
{
  Realtime1.cdwMinutes1++;

  if ((fActive == true) && (enGlobal != GLB_PROGRAM))
  {
    fSendAT = 1;
    EveryMinuteThroughput();
  }

  if ((fActive == true) && (enGlobal == GLB_WORK))
  {
    if (cbShowCurrentTime >= 2)
      ShowCurrTime();
    else
      cbShowCurrentTime++;
  }
}
