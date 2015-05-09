/*------------------------------------------------------------------------------
NEXT_MINUTE1.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_settings.h"
#include "realtime.h"
#include "../keyboard/time/key_timedate.h"



void    NextMinute1(void)
{
  cdwMinutes1++;

  if ((fActive == 1) && (enGlobal == GLB_WORK))
  {
    if (cbShowCurrentTime >= 2)
      ShowCurrentTime();
    else
      cbShowCurrentTime++;
  }
}
