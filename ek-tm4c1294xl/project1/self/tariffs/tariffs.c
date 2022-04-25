/*------------------------------------------------------------------------------
TARIFFS!C

 Ќовый вариант задани€ тарифов
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_tariffs.h"
#include "../memory/mem_program.h"
#include "../memory/mem_settings.h"
#include "../display/display.h"
#include "../nvram/cache.h"
#include "../access.h"
#include "../time/delay.h"
#include "../time/rtc.h"
#include "../time/timedate.h"
#include "zones.h"
#include "oldtariffs.h"
#include "relaxs.h"
#include "gaps.h"
#include "tariffs.h"



cache const             chPublicTrf = {PUBLIC_TRF, &fPublicTrf, sizeof(bool)};
cache const             chPublicTrfPrevMon = {PUBLIC_TRF_PREV_MON, &fPublicTrfPrevMon, sizeof(bool)};

cache const             chOldTrfMode = {OLD_TRF_MODE, &bOldTrfMode, sizeof(uchar)};

cache const             chPeriodTrfPow = {PERIOD_TRF_POW, &mpePeriodTrfPow, sizeof(mpePeriodTrfPow)};
cache const             chPeriodTrfEng = {PERIOD_TRF_ENG, &mpePeriodTrfEng, sizeof(mpePeriodTrfEng)};



bool SaveZonesPow(uchar  ibMonth, uchar  ibMode) {
  return SaveArrayX(ZONES_POW, sizeof(zone), ibMonth*bMODES + ibMode, &mpzoPowMonthMode[ibMonth][ibMode]);
}

bool LoadZonesPow(uchar  ibMonth, uchar  ibMode) {
  return LoadArrayX(ZONES_POW, sizeof(zone), ibMonth*bMODES + ibMode, &mpzoPowMonthMode[ibMonth][ibMode]);
}



bool SaveZonesEng(uchar  ibMonth, uchar  ibMode) {
  return SaveArrayX(ZONES_ENG, sizeof(zone), ibMonth*bMODES + ibMode, &mpzoEngMonthMode[ibMonth][ibMode]);
}

bool LoadZonesEng(uchar  ibMonth, uchar  ibMode) {
  return LoadArrayX(ZONES_ENG, sizeof(zone), ibMonth*bMODES + ibMode, &mpzoEngMonthMode[ibMonth][ibMode]);
}



void    InitTariffs_Custom(void)
{
uchar  ibMonth, ibMode;

  LoadCache(&chPublicTrf);
  LoadCache(&chPublicTrfPrevMon);

  LoadCache(&chOldTrfMode);

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
    for (ibMode=0; ibMode<bMODES; ibMode++)
    {
    	LoadZonesPow(ibMonth, ibMode);
    	LoadZonesEng(ibMonth, ibMode);
    }
  }

  LoadCache(&chPeriodTrfPow);
  LoadCache(&chPeriodTrfEng);

  if (enGlobal == GLB_WORK)
  {
  	MakeAllCurrTariffs();
  }
  else
  {
  	memset(&mpibPowCurrTariff, 0, sizeof(mpibPowCurrTariff));
    memset(&mpibEngCurrTariff, 0, sizeof(mpibEngCurrTariff));
  }
}


void    ResetTariffs(void)
{
  fPublicTrf = false;
  SaveCache(&chPublicTrf);

  fPublicTrfPrevMon = false;
  SaveCache(&chPublicTrfPrevMon);

  bOldTrfMode = 0;
  SaveCache(&chOldTrfMode);

  DefaultTariffs();

  SaveCache(&chPeriodTrfPow);
  SaveCache(&chPeriodTrfEng);
}



void    NextMonTariffs(void)
{
  fPublicTrfPrevMon = fPublicTrf;
  SaveCache(&chPublicTrfPrevMon);
}



void    SetZonePowMonthMode(uchar ibMonth, uchar ibMode, zone *pzo) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  mpzoPowMonthMode[ibMonth][ibMode] = *pzo;
  SaveZonesPow(ibMonth, ibMode);
}


zone  *PGetZonePowMonthMode(uchar ibMonth, uchar ibMode) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  return( &mpzoPowMonthMode[ibMonth][ibMode] );
}



void    SetZoneEngMonthMode(uchar ibMonth, uchar ibMode, zone *pzo) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  mpzoEngMonthMode[ibMonth][ibMode] = *pzo;
  SaveZonesEng(ibMonth, ibMode);
}


zone  *PGetZoneEngMonthMode(uchar ibMonth, uchar ibMode) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  return( &mpzoEngMonthMode[ibMonth][ibMode] );
}



// записывает суточный тарифный график на несколько мес€цев (дл€ энергии)
void    SetZonesEngMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zone *pzo)
{
uchar  ibMonth;

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
    SetZoneEngMonthMode(ibMonth, ibMode, pzo);
}


// записывает суточный тарифный график на несколько мес€цев (дл€ мощности)
void    SetZonesPowMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zone *pzo)
{
uchar  ibMonth;

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
    SetZonePowMonthMode(ibMonth, ibMode, pzo);
}



void    DefaultTariffs(void)
{
  if (fPublicTrf == true)
  {
    SetPeriodTariffsEng(0,11,(zone *)&zoDefaultPow,YEAR);
    SetPeriodTariffsPow(0,11,(zone *)&zoDefaultPow,YEAR);
  }
  else
  {
    SetPeriodTariffsEng(0,11,(zone *)&zoDefaultEng,YEAR);
    SetPeriodTariffsPow(0,11,(zone *)&zoDefaultPow,YEAR);
  }
}



// рассчитывает массив индексов тарифов дл€ каждого получаса текущих суток
void    MakeTariff(uchar  mpTariff[48])
{
uchar   i,j;

  GetZoneAltBreak(0);
  for (j=0; j<48; j++)
    mpTariff[j] = brAlt.ibTariff;

  j = 0;
  for (i=0; i<bBREAKS; i++)
  {
    while (j < GetBreakAltIndex(i))
    {
      GetZoneAltBreak(i);
      mpTariff[j++] = brAlt.ibTariff;
    }
  }
}
// требует предварительной установки переменных zoAlt



// возвращает тип текущих суток относительно списка праздников
uchar   RelaxIndex(time  ti)
{
uchar i;

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);
    if ((tiRelax.bDay   == ti.bDay) &&
        (tiRelax.bMonth == ti.bMonth))
      return tiRelax.bSecond;
  }

  return 0;
}



void    MakeAllCurrTariffs(void)
{
uchar  ibMonth, ibMode;

  time ti = *GetCurrTimeDate();
  if (!ValidTimeDateRTC(ti))
  {
    DelayInf();

#ifndef NO_DISPLAY
    ShowHiDirect(szAlarm);
    ShowLoDirect(szBadTimeRTC);
#endif
  }
  ASSERT(ValidTimeDateRTC(ti));

  if (boGapsFlag == false)
  {
    ibMonth = ti.bMonth - 1;
  }
  else
  {
    MakeGaps();
    ibMonth = mpbGaps[GetDayIndexMD(ti.bMonth, ti.bDay)];
  }

  ibMode  = GetMode(ti);

  zoAlt = *PGetZoneEngMonthMode(ibMonth,ibMode);
  MakeTariff(mpibEngCurrTariff);

  zoAlt = *PGetZonePowMonthMode(ibMonth,ibMode);
  MakeTariff(mpibPowCurrTariff);

  if (boRelaxsFlag == true)
  {
    uchar j = RelaxIndex(ti);
    uchar i = GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay);

    if ((j != 2) && ((i == 5) || (i == 6) || (j == 1)))
    {
      i = ibRelaxsTariff;
      if (i >= bTARIFFS) i = 0;

      // memset(&mpibEngCurrTariff, i, sizeof(mpibEngCurrTariff));
      memset(&mpibPowCurrTariff, i, sizeof(mpibPowCurrTariff));
    }
  }
}


void    MakeAllPrevTariffs(time  ti)
{
uchar  i, j;
uchar  ibMonth, ibMode;

  ibMonth = ti.bMonth - 1;

  if (boGapsFlag == false)
  {
    ibMonth = ti.bMonth - 1;
  }
  else
  {
    MakeGaps();
    ibMonth = mpbGaps[GetDayIndexMD(ti.bMonth, ti.bDay)];
  }

  ibMode  = GetMode(ti);

  zoAlt = *PGetZoneEngMonthMode(ibMonth,ibMode);
  MakeTariff(mpibEngPrevTariff);

  zoAlt = *PGetZonePowMonthMode(ibMonth,ibMode);
  MakeTariff(mpibPowPrevTariff);

  if (boRelaxsFlag == true)
  {
    j = RelaxIndex(ti);
    i = GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay);

    if ((j != 2) && ((i == 5) || (i == 6) || (j == 1)))
    {
      i = ibRelaxsTariff;
      if (i >= bTARIFFS) i = 0;

      // memset(&mpibEngPrevTariff, i, sizeof(mpibEngPrevTariff));
      memset(&mpibPowPrevTariff, i, sizeof(mpibPowPrevTariff));
    }
  }
}
