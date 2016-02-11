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
  memset(&mpdbEngFracDigCan, 0, sizeof(mpdbEngFracDigCan));
  memset(&mtiProcedure31Dig, 0, sizeof(mtiProcedure31Dig));
}



bool    IsCleanProcedure31(uchar  ibDig)
{
  return mtiProcedure31Dig[ibDig].bYear == 0;
}


uchar   GetProcedure31Idx(time  ti)
{
  return (((ti.bHour + 24)*60 + ti.bMinute - 1) / 30) % 48;
}



void    AddProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  db)
{
  mtiProcedure31Dig[ibDig] = ti;

  MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000); MonitorString("+"); MonitorLongDec(db*1000);
  db /= 1000;
  mpdbEngFracDigCan[ibDig][ibCan] += db;
  MonitorString("="); MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000);
}


void    SubProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  dbPulse)
{
  MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000);
  uint w = (uint)(mpdbEngFracDigCan[ibDig][ibCan]*dbPulse);
  MonitorString("="); MonitorIntDec(w);
  mpwChannels[ibCan] = w;

  mpdbEngFracDigCan[ibDig][ibCan] -= (double)w/dbPulse;
  MonitorString("+"); MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000);
}
