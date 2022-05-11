/*------------------------------------------------------------------------------
periodic_reset.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/restart.h"
#include "../kernel/settings.h"
#include "clock.h"
#include "periodic_reset.h"



void RunPeriodicReset(void) {
  if ((fPeriodicResetFlag == 1) && (wPeriodicResetPeriod <= 1440))
  {
    uint minutes = GetClockSeconds() / 60;
    if (minutes >= wPeriodicResetPeriod)
    {
      Restart();
    }
  }
}
