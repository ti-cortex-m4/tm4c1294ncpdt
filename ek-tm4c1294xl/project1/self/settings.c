/*------------------------------------------------------------------------------
SETTINGS,C


------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_settings.h"
#include "memory/mem_program.h"
#include "flash/files.h"
#include "nvram/cache.h"
#include "time/timedate.h"
#include "label_global.h"
#include "settings.h"



file const              flPrivate = {PRIVATE, &wPrivate, sizeof(uint)};
cache const             chLogical = {LOGICAL, &bLogical, sizeof(uchar)};

cache const             chFirstReset = {FIRST_RESET, &boFirstReset, sizeof(bool)};

cache const             chSetTime = {SET_TIME, &boSetTime, sizeof(bool)};
cache const             chSetDate = {SET_DATE, &boSetDate, sizeof(bool)};
cache const             chSetGroups = {SET_GROUPS, &boSetGroups, sizeof(bool)};
cache const             chSetPassword = {SET_PASSWORD, &boSetPassword, sizeof(bool)};

cache const             chStart = {START, &tiStart, sizeof(time)};
cache const             chPowerOff = {POWER_OFF, &tiPowerOff, sizeof(time)};
cache const             chPowerOn = {POWER_ON, &tiPowerOn, sizeof(time)};
cache const             chSwitchOn = {SWITCH_ON, &cbSwitchOn, sizeof(uchar)};



void    InitSettings(void)
{
  enGlobal = GetLabelGlobal() ? GLB_WORK : GLB_PROGRAM;

  if (LoadFile(&flPrivate) == false)
  {
    wPrivate = 1;
    SaveFile(&flPrivate);
  }

  LoadCache(&chLogical);

  LoadCache(&chFirstReset);

  LoadCache(&chSetTime);
  LoadCache(&chSetDate);
  LoadCache(&chSetGroups);
  LoadCache(&chSetPassword);

  LoadCache(&chStart);
  LoadCache(&chPowerOff);
  LoadCache(&chPowerOn);
  LoadCache(&chSwitchOn);
}


void    ResetSettings(bool  fFull)
{
  if (fFull)
  {
    bLogical = 1;
    SaveCache(&chLogical);
  }

  boFirstReset = false;
  SaveCache(&chFirstReset);

  if (fFull)
  {
    boSetTime = false;
    SaveCache(&chSetTime);

    boSetDate = false;
    SaveCache(&chSetDate);

    boSetPassword = true;
    SaveCache(&chSetPassword);
  }

  tiStart = tiZero;
  SaveCache(&chStart);

  tiPowerOff = tiZero;
  SaveCache(&chPowerOff);

  tiPowerOn = tiZero;
  SaveCache(&chPowerOn);

  cbSwitchOn = 0;
  SaveCache(&chSwitchOn);
}
