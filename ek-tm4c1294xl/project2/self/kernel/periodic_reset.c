/*------------------------------------------------------------------------------
periodic_reset.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../kernel/settings.h"
#include "clock.h"
#include "periodic_reset.h"



void RunPeriodicReset(void) {
  if ((fPeriodicResetFlag == 1) && (wPeriodicResetFlag <= 1440))
  {
    if (GetClockSeconds() / 60)
    {
    }
  }
}
