/*------------------------------------------------------------------------------
PROCEDURE31.C


------------------------------------------------------------------------------*/


#include "../../main.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_energy_spec.h"
#include "../../serial/monitor.h"
#include "../../special/special31.h"
#include "procedure31.h"



time                    mtiProcedure31Dig[bCANALS];



void    InitProcedure31(void)
{
  ClearProcedure31(true,true);
}


void    ClearProcedure31(bool  fClearValue, bool  fClearTime)
{
  if (fClearValue)
  {
    MonitorString("\n clear procedure value");
    memset(&mpdbEngFracDigCan, 0, sizeof(mpdbEngFracDigCan));
  }

  if (fClearTime)
  {
    MonitorString("\n clear procedure time");
    memset(&mtiProcedure31Dig, 0, sizeof(mtiProcedure31Dig));
  }
}



uchar   GetProcedure31Idx(time  ti)
{
  return (((ti.bHour + 24)*60 + ti.bMinute - 1) / 30) % 48;
}



static void MonitorBuff(uchar  ibDig, uchar  ibCan)
{
  MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000);
}


void    AddProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  db)
{
  mtiProcedure31Dig[ibDig] = ti;

  MonitorLongDec(mpdbChannels31[ibCan]); MonitorString("+"); MonitorLongDec(db);

  mpdbChannels31[ibCan] += (db/1000);

  MonitorString("="); MonitorLongDec(mpdbChannels31[ibCan]);
}


void    SubProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  dbPulse)
{
//  MonitorBuff(ibDig,ibCan);
//  uint w = (uint)(mpdbEngFracDigCan[ibDig][ibCan]*dbPulse);
//
//  MonitorString("="); MonitorIntDec(w);
//  mpwChannels[ibCan] = w;
//
//  mpdbEngFracDigCan[ibDig][ibCan] -= (double)w/dbPulse;
//  MonitorString("+"); MonitorBuff(ibDig,ibCan);
}
