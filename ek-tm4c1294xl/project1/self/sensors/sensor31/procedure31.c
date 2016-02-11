/*------------------------------------------------------------------------------
PROCEDURE31.C


------------------------------------------------------------------------------*/


#include "../../main.h"
#include "../../memory/mem_energy_spec.h"
#include "../../serial/monitor.h"
#include "procedure31.h"



time                    mtiProcedureDig[bCANALS];



void    ClearProcedure(void)
{
  memset(&mpdbEngFracDigCan, 0, sizeof(mpdbEngFracDigCan));
  memset(&mtiProcedureDig, 0, sizeof(mtiProcedureDig));
}


bool    IsCleanProcedure(uchar  ibDig)
{
  return mtiProcedureDig[ibDig].bYear == 0;
}


void    AddProcedure(time  ti, uchar  ibDig, uchar  ibCan, double  db)
{
  mtiProcedureDig[ibDig] = ti;

  MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000); MonitorString("+"); MonitorLongDec(db*1000);
  db /= 1000;
  mpdbEngFracDigCan[ibDig][ibCan] += db;
  MonitorString("="); MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000);
}


void    SubProcedure(time  ti, uchar  ibDig, uchar  ibCan, double  dbPulse)
{
  MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000);
  uint w = (uint)(mpdbEngFracDigCan[ibDig][ibCan]*dbPulse);
  MonitorString("="); MonitorIntDec(w);
  mpwChannels[ibCan] = w;

  mpdbEngFracDigCan[ibDig][ibCan] -= (double)w/dbPulse;
  MonitorString("+"); MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000);
}


uchar   GetTimeIdx(time  ti)
{
  return (((ti.bHour + 24)*60 + ti.bMinute - 1) / 30) % 48;
}
