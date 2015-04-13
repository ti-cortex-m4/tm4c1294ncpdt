/*------------------------------------------------------------------------------
RECALC_DEF.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_energy.h"
#include        "../memory/mem_energy_spec.h"
#include        "../realtime/realtime.h"
#include        "../flash/files.h"
#include        "recalc_def.h"



boolean SaveDefDay(uchar  ibDayTo)
{
  return SaveBuff(FLS_DEFDAYCAN + ibDayTo*bIMPULSE_CAN, mpdeDayCan, sizeof(mpdeDayCan));
}


boolean LoadDefDay(uchar  ibDayFrom)
{
  return LoadBuff(FLS_DEFDAYCAN + ibDayFrom*bIMPULSE_CAN, mpdeDayCan, sizeof(mpdeDayCan));
}



boolean SaveDefMon(uchar  ibMonTo)
{
  return SaveBuff(FLS_DEFMONCAN + ibMonTo*bIMPULSE_CAN, mpdeMonCan, sizeof(mpdeMonCan));
}


boolean LoadDefMon(uchar  ibMonFrom)
{
  return LoadBuff(FLS_DEFMONCAN + ibMonFrom*bIMPULSE_CAN, mpdeMonCan, sizeof(mpdeMonCan));
}



void    InitDef(void)
{
}


void    ResetDef(void)
{
  memset(&mpdeDayCan, 0, sizeof(mpdeDayCan));

  uchar d;
  for (d=0; d<bDAYS; d++)
    SaveDefDay(d);

  memset(&mpdeMonCan, 0, sizeof(mpdeMonCan));

  uchar m;
  for (m=0; m<bMONTHS; m++)
    SaveDefMon(m);
}



void    NextDayDef(void) 
{
  memset(&mpdeDayCan, 0, sizeof(mpdeDayCan));
  SaveDefDay(ibHardDay);
}


void    NextMonDef(void) 
{
  memset(&mpdeMonCan, 0, sizeof(mpdeMonCan));
  SaveDefMon(ibHardMon);
}



void    MakeDefSpec(impulse  *mpimT, uchar  ibCan, time  *pti)
{
  uchar i = pti->bHour*2 + pti->bMinute/30;
  uchar t = mpibEngPrevTariff[i];
  ulong dw = mpimT[ibCan].mpdwImp[t];

  if (mpwImpHouCanDef[ibCan] != 0xFFFF)
    dw++;

  mpimT[ibCan].mpdwImp[t] = dw;
}

