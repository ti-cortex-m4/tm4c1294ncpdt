/*------------------------------------------------------------------------------
SPECIAL31!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_energy_spec.h"
#include "../display/display.h"
#include "../tariffs/tariffs.h"
#include "../impulses/energy_spec.h"
#include "../devices/devices.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../time/decret.h"
#include "../energy.h"
#include "../kernel/arrays_buff.h"
#include "calc.h"
#include "special31.h"



bool    MakeSpecial31(time  ti)
{
  if (IsDefect(ibDig) || IsWinterDouble(ibDig, ti))
  {
    cwHouRead++;
    sprintf(szLo," %02u:%02u",ti.bHour,ti.bMinute);

    CalcTimeDate(1, 1, ti);


    MakeAllPrevTariffs(ti);

    CalcDigCanals(ti);

    fLoadMem = 0;
    CalcAllGroups(1, ti);

    return true;
  }

  return false;
}
