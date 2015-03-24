/*------------------------------------------------------------------------------
DEFECTS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy_spec.h"
#include        "../time/timedate.h"
#include        "../time/rtc.h"



void    MakeDefectDay(uchar  ibDay, time  *pti)
{
  pti->bHour   = 0;
  pti->bMinute = 0;
  pti->bSecond = 0;

  mpdeDay[ (bDAYS + ibHardDay - ibDay) % bDAYS ] = *pti;
}


void    MakeDefectMon(uchar  ibMon, time  *pti)
{
  pti->bDay    = 1;
  pti->bHour   = 0;
  pti->bMinute = 0;
  pti->bSecond = 0;

  mpdeMon[ (bMONTHS + ibHardMon - ibMon) % bMONTHS ] = *pti;
}



void    MakeAllDefects(void)
{
time    ti;

  ti = *GetCurrTimeDate();

  uint d;
  for (d=0; d<bDAYS; d++)
  {
    MakeDefectDay(d, &ti);

    if (ti.bDay > 1)
      ti.bDay--;
    else
    {
      if (ti.bMonth > 1)
        ti.bMonth--;
      else
      {
        ti.bMonth = 12;
        ti.bYear--;
      }
      ti.bDay = GetDaysInMonthYM(ti.bYear, ti.bMonth);
    }
  }

  ti = *GetCurrTimeDate();

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    MakeDefectMon(m, &ti);

    if (ti.bMonth > 1)
      ti.bMonth--;
    else
    {
      ti.bMonth = 12;
      ti.bYear--;
    }
  }
}
