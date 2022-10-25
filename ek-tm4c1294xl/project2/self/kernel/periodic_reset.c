/*------------------------------------------------------------------------------
periodic_reset.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/delay.h"
#include "../hardware/hardware_restart.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "clock.h"
#include "periodic_reset.h"



void RunPeriodicReset(void) {
  if ((fPeriodicResetFlag == 1) && (wPeriodicResetPeriod >= 1) && (wPeriodicResetPeriod <= 1440))
  {
    uint minutes = GetClockSeconds() / 60;
    if (minutes >= wPeriodicResetPeriod)
    {
      CONSOLE("periodic restart \n");
      DelaySecond(1);

      //Restart();
      HardwareRestart();
    }
  }
}
