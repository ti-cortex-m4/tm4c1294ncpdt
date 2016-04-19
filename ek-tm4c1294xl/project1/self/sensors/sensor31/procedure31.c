/*------------------------------------------------------------------------------
PROCEDURE31.C


------------------------------------------------------------------------------*/


#include "../../main.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_energy_spec.h"
#include "../../display/display.h"
#include "../../tariffs/tariffs.h"
#include "../../impulses/energy_spec.h"
#include "../../digitals/digitals.h"
#include "../../digitals/profile/profile_frac.h"
#include "../../devices/devices.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../time/decret.h"
#include "../../energy.h"
#include "../../kernel/arrays_buff.h"
#include "../../serial/monitor.h"
#include "../../sensors/sensor31/procedure31.h"
#include "../../special/calc.h"
#include "../../special/recalc_def.h"
#include "../../special/special.h"
#include "procedure31.h"



time                    mtiProcedure31Dig[bCANALS];

double                  mpdbChannelsPrev31[bCHANNELS],
                        mpdbChannelsCurr31[bCHANNELS];



static void MonitorBuff(uchar  ibDig, uchar  i)
{
  MonitorLongDec(mpdbEngFracDigCan[ibDig][i]*1000);
}

static void MonitorChannelsCurr(uchar  i)
{
  MonitorLongDec(mpdbChannelsCurr31[i]*1000);
}

static void MonitorChannelsPrev(uchar  i)
{
  MonitorLongDec(mpdbChannelsPrev31[i]*1000);
}



void    ClearChannels31(void)
{
  memset(&mpdbChannelsPrev31, 0, sizeof(mpdbChannelsPrev31));
  memset(&mpdbChannelsCurr31, 0, sizeof(mpdbChannelsCurr31));
}


void    ClearProcedure31(bool  fClearTime)
{
  if (fClearTime)
  {
    MonitorString("\n clear procedure time");
    memset(&mtiProcedure31Dig, 0, sizeof(mtiProcedure31Dig));
  }
}


void    InitProcedure31(void)
{
  ClearProcedure31(true);
}


void    StartProcedure31(void)
{
  ClearProcedure31(true);
  ClearChannels31();
}



uchar   GetProcedure31Idx(time  ti)
{
  return (((ti.bHour + 24)*60 + ti.bMinute - 1) / 30) % 48;
}



void    AddProcedure31(time  ti, uchar  ibDig, uchar  i, double  db)
{
  MonitorString(" prev. ");

  mtiProcedure31Dig[ibDig] = ti;

  MonitorChannelsPrev(i); MonitorString("+"); MonitorLongDec(db);
  mpdbChannelsPrev31[i] += (db/1000);
  MonitorString("="); MonitorChannelsPrev(i);
}


void    SubProcedure31(time  ti, uchar  ibDig, uchar  i)
{
  MonitorString(" curr. ");

  MonitorChannelsCurr(i);
  mpdbChannelsCurr31[i] = mpdbChannelsPrev31[i];
  MonitorString("->"); MonitorChannelsCurr(i);

  mpdbChannelsPrev31[i] = 0;
}


void    CalcDigCanals31(uchar  bMaxLine)
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

  SaveProfileFrac6(ibDig);
}


bool    MakeSpecial31(time  ti, uchar  bMaxLine)
{
  if (IsDefect(ibDig) || IsWinterDouble(ibDig, ti))
  {
    cwHouRead++;
    sprintf(szLo," %02u:%02u",ti.bHour,ti.bMinute);

    CalcTimeDate(1, 1, ti);


    MakeAllPrevTariffs(ti);

    CalcDigCanals31(bMaxLine);
    CalcDigCanals(ti);

    fLoadMem = 0;
    CalcAllGroups(1, ti);

    return true;
  }

  return false;
}
