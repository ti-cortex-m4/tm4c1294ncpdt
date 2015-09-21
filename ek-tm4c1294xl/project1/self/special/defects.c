/*------------------------------------------------------------------------------
DEFECTS.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../time/timedate.h"
#include "../time/rtc.h"
#include "defects.h"



void    MakeDefectDay(uchar  ibDay, time  ti)
{
  ti.bHour   = 0;
  ti.bMinute = 0;
  ti.bSecond = 0;

  mpdeDay[ (bDAYS + ibHardDay - ibDay) % bDAYS ] = ti;
}


void    MakeDefectMon(uchar  ibMon, time  ti)
{
  ti.bDay    = 1;
  ti.bHour   = 0;
  ti.bMinute = 0;
  ti.bSecond = 0;

  mpdeMon[ (bMONTHS + ibHardMon - ibMon) % bMONTHS ] = ti;
}



void    MakeAllDefects(void)
{
  time ti = *GetCurrTimeDate();
  ASSERT(IsValidTimeDateRTC(ti));

  uchar d;
  for (d=0; d<bDAYS; d++)
  {
    MakeDefectDay(d, ti);

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
    MakeDefectMon(m, ti);

    if (ti.bMonth > 1)
      ti.bMonth--;
    else
    {
      ti.bMonth = 12;
      ti.bYear--;
    }
  }
}



void    InitDefects_Custom(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    memset(&mpdeDay, 0, sizeof(mpdeDay));
    memset(&mpdeMon, 0, sizeof(mpdeMon));
  }
  else
  {
    MakeAllDefects();
  }
}


void    StartDefects(void)
{
  MakeAllDefects();
}
