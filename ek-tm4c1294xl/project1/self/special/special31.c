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
#include "calc.h"
#include "recalc_def.h"
#include "special.h"
#include "special31.h"



double                  mpdbChannelsA31[bCHANNELS],mpdbChannelsB31[bCHANNELS];



void    CalcChannels31(void)
{
  MonitorString("\n CALC");
  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<6; i++)
  {
    MonitorString("\n +B "); MonitorLongDec(mpdbChannelsB31[i]*1000);
    mpdbEngFracDigCan[ibDig][i] += mpdbChannelsB31[i];
    mpdbChannelsB31[i] = 0;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse);
    MonitorString(" w "); MonitorIntDec(w);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w/dbPulse;
  }
}


void    CalcDigCanals31(time  ti)
{
  LoadImpHouSpec(iwDigHou,1);

  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == true)
    {
      uint w;
      if (iwDigHou == iwHardHou)
        w = 0xFFFF;
      else
      {
        w = mpwChannels[ diPrev.ibLine ];

        if (IsWinterDouble(c, ti) && (mpwImpHouCanSpec[c] != 0xFFFF))
        {
          w += mpwImpHouCanSpec[c];
          mpbWinterCan[c]++;

          if (fLoadDay == 1) MakeImpSpec_Winter( mpimDayCanSpec, c, ti );
          if (fLoadMon == 1) MakeImpSpec_Winter( mpimMonCanSpec, c, ti );
        }
      }

      mpwImpHouCanSpec[c] = w;
      mpwImpHouCanDef[c] = w;

      mpboReadyCan[c] = true;
      mpcwCalcDig[c]++;

      if (fLoadDay == 1) MakeImpSpec( mpimDayCanSpec, c, ti );
      if (fLoadMon == 1) MakeImpSpec( mpimMonCanSpec, c, ti );

      if (fLoadDay == 1) MakeDefSpec( mpdeDayCan, c, ti );
      if (fLoadMon == 1) MakeDefSpec( mpdeMonCan, c, ti );
    }
  }

  SaveImpHouSpec(1,iwDigHou);
}



bool    MakeSpecial31(time  ti)
{
  if (IsDefect(ibDig) || IsWinterDouble(ibDig, ti))
  {
    cwHouRead++;
    sprintf(szLo," %02u:%02u",ti.bHour,ti.bMinute);

    CalcTimeDate(1, 1, ti);


    MakeAllPrevTariffs(ti);

    CalcChannels31();
    CalcDigCanals31(ti);

    fLoadMem = 0;
    CalcAllGroups(1, ti);

    return true;
  }

  return false;
}
