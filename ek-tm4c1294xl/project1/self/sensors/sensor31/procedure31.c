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



void    AddProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  db)
{
  MonitorString("\n prev");

  mtiProcedure31Dig[ibDig] = ti;

  MonitorChannelsPrev(ibCan); MonitorString("+"); MonitorLongDec(db);
  mpdbChannelsPrev31[ibCan] += (db/1000);
  MonitorString("="); MonitorChannelsPrev(ibCan);
}


void    SubProcedure31(time  ti, uchar  ibDig, uchar  ibCan, double  dbPulse)
{
  MonitorString("\n curr.");

  MonitorChannelsCurr(ibCan);
  mpdbChannelsCurr31[ibCan] = mpdbChannelsPrev31[ibCan];
  MonitorString(" "); MonitorChannelsCurr(ibCan);

  mpdbChannelsPrev31[ibCan] = 0;
}
