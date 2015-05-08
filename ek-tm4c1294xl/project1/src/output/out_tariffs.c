/*------------------------------------------------------------------------------
 OUT_TARIFFS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_tariffs.h"
#include "../keyboard/keyboard.h"
#include "../serial/ports.h"
#include "../access.h"
#include "../flash/files.h"
#include "../tariffs/tariffs.h"
#include "../tariffs/oldtariffs.h"
#include "../tariffs/zones.h"



void    OutGetPublicTariffs(void)
{
  LongResult(fPublicTariffs);
}


void    OutSetPublicTariffs(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if (ValidBoolean(bInBuff5))
    {
      fPublicTariffs = CharToBoolean(bInBuff5);
      SaveFile(&flPublicTariffs);
      Result(bRES_OK);
    }
    else Result(bRES_BADDATA);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetOldPowTariffs(void)
{
  if ((fPublicTariffs == FALSE) || (SuperUser() == true))
  {
    if (bInBuff5 < 12)
      Common(PGetZonePowMonthMode(bInBuff5, 0), sizeof(zone));
    else
      Result(bRES_BADDATA);
  }
  else Result(bRES_BADMODE);
}


void    OutSetOldPowTariffs(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if (bInBuff5 < 12)
    {
      InitPop(7);

      zone zo;
      Pop(&zo, sizeof(zone));

      if (TrueZone(&zo))
      {
        SetPeriodTariffsPow(bInBuff5, bInBuff5, &zo, YEAR);
        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetOldEngTariffs(void)
{
  if ((fPublicTariffs == FALSE) || (SuperUser() == true))
  {
    if (bInBuff5 < 12)
      Common(PGetZoneEngMonthMode(bInBuff5, 0), sizeof(zone));
    else
      Result(bRES_BADDATA);
  }
  else Result(bRES_BADMODE);
}


void    OutSetOldEngTariffs(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if (bInBuff5 < 12)
    {
      InitPop(7);

      zone zo;
      Pop(&zo, sizeof(zone));

      if (TrueZone(&zo))
      {
        SetPeriodTariffsEng(bInBuff5, bInBuff5, &zo, YEAR);
        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetOldPubTariffs(void)
{
  if ((fPublicTariffs == TRUE) || (SuperUser() == true))
  {
    if (bInBuff5 < 12)
      Common(PGetZonePowMonthMode(bInBuff5, 0), sizeof(zone));
    else
      Result(bRES_BADDATA);
  }
  else Result(bRES_BADMODE);
}


void    OutSetOldPubTariffs(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if (bInBuff5 < 12)
    {
      InitPop(7);

      zone zo;
      Pop(&zo, sizeof(zone));

      if (TrueZone(&zo))
      {
        SetPeriodTariffsPow(bInBuff5, bInBuff5, &zo, YEAR);
        SetPeriodTariffsEng(bInBuff5, bInBuff5, &zo, YEAR);
        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetNewPowTariffs(void)
{
  if (fPublicTariffs == FALSE)
  {
    if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
      Common(PGetZonePowMonthMode(bInBuff5, bInBuff6), sizeof(zone));
    else
      Result(bRES_BADDATA);
  }
  else Result(bRES_BADMODE);
}


void    OutSetNewPowTariffs(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
    {
      InitPop(7);

      zone zo;
      Pop(&zo, sizeof(zone));

      if (TrueZone(&zo))
      {
        SetZonesPowMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zo);
        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetNewEngTariffs(void)
{
  if (fPublicTariffs == FALSE)
  {
    if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
      Common(PGetZoneEngMonthMode(bInBuff5, bInBuff6), sizeof(zone));
    else
      Result(bRES_BADDATA);
  }
  else Result(bRES_BADMODE);
}


void    OutSetNewEngTariffs(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
    {
      InitPop(7);

      zone zo;
      Pop(&zo, sizeof(zone));

      if (TrueZone(&zo))
      {
        SetZonesEngMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zo);
        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetNewPubTariffs(void)
{
  if (fPublicTariffs == TRUE)
  {
    if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
      Common(PGetZonePowMonthMode(bInBuff5, bInBuff6), sizeof(zone));
    else
      Result(bRES_BADDATA);
  }
  else Result(bRES_BADMODE);
}


void    OutSetNewPubTariffs(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if ((bInBuff5 < 12) && (bInBuff6 < bMODES))
    {
      InitPop(7);

      zone zo;
      Pop(&zo, sizeof(zone));

      if (TrueZone(&zo))
      {
        SetZonesPowMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zo);
        SetZonesEngMonthsMode(bInBuff5, bInBuff5, bInBuff6, &zo);
        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetTariffsDay(void)
{
  InitPushPtr();
  Push(&mpibPowCurrTariff, 48);
  Push(&mpibEngCurrTariff, 48);
  OutptrOutBuff(2 * 48);
}



void    OutGetAllPowTariffs(void)
{
  Common(&mpzoPowMonthMode, sizeof(mpzoPowMonthMode));
}


void    OutGetAllEngTariffs(void)
{
  Common(&mpzoEngMonthMode, sizeof(mpzoEngMonthMode));
}

