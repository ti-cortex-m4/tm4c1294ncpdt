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



void    AddProcedure31(time  ti, uchar  ibDig, uchar  i, double  db)
{
  MonitorString(" prev. ");

  mtiProcedure31Dig[ibDig] = ti;

  MonitorChannelsPrev(i); MonitorString("+"); MonitorLongDec(db);
  mpdbChannelsPrev31[i] += (db/1000);
  MonitorString("="); MonitorChannelsPrev(i);
}


void    SubProcedure31(time  ti, uchar  ibDig, uchar  i, double  dbPulse)
{
  MonitorString(" curr. ");

  MonitorChannelsCurr(i);
  mpdbChannelsCurr31[i] = mpdbChannelsPrev31[i];
  MonitorString("->"); MonitorChannelsCurr(i);

  mpdbChannelsPrev31[i] = 0;
}
