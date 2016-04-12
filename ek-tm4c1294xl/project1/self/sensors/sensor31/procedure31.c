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



/*static*/ void MonitorBuff(uchar  ibDig, uchar  ibCan)
{
  MonitorLongDec(mpdbEngFracDigCan[ibDig][ibCan]*1000);
}


void    AddProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  db)
{
  MonitorString("\n ADD ");

  mtiProcedure31Dig[ibDig] = ti;

  MonitorLongDec(mpdbChannelsA31[ibCan]*1000); MonitorString("+"); MonitorLongDec(db);

  mpdbChannelsA31[ibCan] += (db/1000);

  MonitorString("=A "); MonitorLongDec(mpdbChannelsA31[ibCan]*1000);
}


void    SubProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  dbPulse)
{
  MonitorString("\n SUB ");

  mpdbChannelsB31[ibCan] = mpdbChannelsA31[ibCan];
  MonitorString(" +B "); MonitorLongDec(mpdbChannelsB31[ibCan]*1000);

  mpdbChannelsA31[ibCan] = 0;
}
