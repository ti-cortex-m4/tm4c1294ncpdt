/*------------------------------------------------------------------------------
PROCEDURE31.C


------------------------------------------------------------------------------*/


#include "../../main.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_energy_spec.h"
#include "../../serial/monitor.h"
#include "procedure31.h"



time                    mtiProcedure31Dig[bCANALS];



void    ClearProcedure31(void)
{
  MonitorString("\n clear procedure");
  memset(&mpdbEngFracDigCan, 0, sizeof(mpdbEngFracDigCan));
  memset(&mtiProcedure31Dig, 0, sizeof(mtiProcedure31Dig));
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

  MonitorBuff(ibDig,ibCan); MonitorString("+"); MonitorLongDec(db);

  mpdbEngFracDigCan[ibDig][ibCan] += (db/1000);

  MonitorString("="); MonitorBuff(ibDig,ibCan);
}


void    SubProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  dbPulse)
{
  MonitorBuff(ibDig,ibCan);
  uint w = (uint)(mpdbEngFracDigCan[ibDig][ibCan]*dbPulse);

  MonitorString("="); MonitorIntDec(w);
  mpwChannels[ibCan] = w;

  mpdbEngFracDigCan[ibDig][ibCan] -= (double)w/dbPulse;
  MonitorString("+"); MonitorBuff(ibDig,ibCan);
}
