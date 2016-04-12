/*------------------------------------------------------------------------------
SPECIAL31!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_energy_spec.h"
#include "../display/display.h"
#include "../tariffs/tariffs.h"
#include "../impulses/energy_spec.h"
#include "../digitals/digitals.h"
#include "../devices/devices.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../time/decret.h"
#include "../energy.h"
#include "../kernel/arrays_buff.h"
#include "../serial/monitor.h"
#include "../sensors/sensor31/procedure31.h"
#include "calc.h"
#include "recalc_def.h"
#include "special.h"
#include "special31.h"



double                  mpdbChannelsPrev31[bCHANNELS],
                        mpdbChannelsCurr31[bCHANNELS];



void    CalcChannels31(uchar  bMaxLine)
{
  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<bMaxLine; i++)
  {
    MonitorBuff(ibDig,i); MonitorString("+"); MonitorLongDec(mpdbChannelsCurr31[i]*1000);
    mpdbEngFracDigCan[ibDig][i] += mpdbChannelsCurr31[i];
    mpdbChannelsCurr31[i] = 0;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse);
    MonitorString(" = "); MonitorIntDec(w);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w/dbPulse;
    MonitorString("+"); MonitorBuff(ibDig,i);
  }
}



bool    MakeSpecial31(time  ti, uchar  bMaxLine)
{
  if (IsDefect(ibDig) || IsWinterDouble(ibDig, ti))
  {
    cwHouRead++;
    sprintf(szLo," %02u:%02u",ti.bHour,ti.bMinute);

    CalcTimeDate(1, 1, ti);


    MakeAllPrevTariffs(ti);

    CalcChannels31(bMaxLine);
    CalcDigCanals(ti);

    fLoadMem = 0;
    CalcAllGroups(1, ti);

    return true;
  }

  return false;
}
