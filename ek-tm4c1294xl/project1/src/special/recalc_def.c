/*------------------------------------------------------------------------------
RECALC_DEF.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../memory/mem_energy_spec.h"
#include        "../realtime/realtime.h"
#include        "../flash/files.h"



bool    SaveDefDay(uchar  ibDayTo)
{
  OpenOut(FLS_DEFDAYCAN + ibDayTo*bIMPULSE_CAN);

  if (Save(mpdeDayCan, sizeof(impulse)*bCANALS) == 0)
    return(0);

  return( CloseOut() );
}


bool    LoadDefDay(uchar  ibDayFrom)
{
  OpenIn(FLS_DEFDAYCAN + ibDayFrom*bIMPULSE_CAN);
  return( Load(mpdeDayCan, sizeof(impulse)*bCANALS) );
}



bool    SaveDefMon(uchar  ibMonTo)
{
  OpenOut(FLS_DEFMONCAN + ibMonTo*bIMPULSE_CAN);

  if (Save(mpdeMonCan, sizeof(impulse)*bCANALS) == 0)
    return(0);

  return( CloseOut() );
}


bool    LoadDefMon(uchar  ibMonFrom)
{
  OpenIn(FLS_DEFMONCAN + ibMonFrom*bIMPULSE_CAN);
  return( Load(mpdeMonCan, sizeof(impulse)*bCANALS) );
}


/*
void    ResetFlashDef(void)
{
uchar   i;

  memset(&mpdeDayCan, 0, sizeof(mpdeDayCan));
  for (i=0; i<bDAYS; i++)
    SaveDefDay(i);

  memset(&mpdeMonCan, 0, sizeof(mpdeMonCan));
  for (i=0; i<bMONTHS; i++)
    SaveDefMon(i);
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
*/


void    MakeDefSpec(impulse  *mpimT)
{
  uchar j = mpibEngPrevTariff[ tiAlt.bHour*2 + tiAlt.bMinute/30 ];
  ulong dw = mpimT[ibCan].mpdwImp[j];

  if (mpwImpHouCanDef[ibCan] != 0xFFFF)
    dw++;

  mpimT[ibCan].mpdwImp[j] = dw;
}

