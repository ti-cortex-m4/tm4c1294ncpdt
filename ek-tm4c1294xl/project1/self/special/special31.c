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



void    MonitorBuff(uchar  ibDig, uchar  ibCan)
{
  MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000);
}


void    MonitorChannelsCurr(uchar  ibCan)
{
  MonitorLongDec(mpdbChannelsCurr31[ibCan]*1000);
}


void    MonitorChannelsPrev(uchar  ibCan)
{
  MonitorLongDec(mpdbChannelsPrev31[ibCan]*1000);
}



void    ClearChannels31(void)
{
  memset(&mpdbChannelsPrev31, 0, sizeof(mpdbChannelsPrev31));
  memset(&mpdbChannelsCurr31, 0, sizeof(mpdbChannelsCurr31));
}



void    CalcChannels31(uchar  bMaxLine)
{
  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<bMaxLine; i++)
  {
    MonitorString("\n value2 "); MonitorBuff(ibDig,i); MonitorString("+"); MonitorChannelsCurr(i);
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
