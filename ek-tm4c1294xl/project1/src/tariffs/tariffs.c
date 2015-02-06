/*------------------------------------------------------------------------------
TARIFFS.C

 Ќовый вариант задани€ тарифов
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_program.h"
#include        "../memory/mem_settings.h"
#include        "../display/display.h"
#include        "../delay.h"
#include        "../flash/files.h"
#include        "../access.h"
#include        "../rtc.h"
#include        "../timedate.h"
#include        "zones.h"
#include        "oldtariffs.h"
#include        "relaxs.h"
#include        "gaps.h"
#include        "tariffs.h"



file const              flPublicTariffs = {wFLA_PUBLIC_TARIFFS, &fPublicTariffsCurr, sizeof(boolean)};
file const              flOldTariffsMode = {wFLA_OLD_TARIFFS_MODE, &bOldTariffsMode, sizeof(uchar)};



boolean SaveZonesPow(uchar  ibMonth, uchar  ibMode) {
	return SaveBuff(wFLA_ZONES_POW + ibMonth*bMODES + ibMode, &mpzoPowMonthMode[ibMonth][ibMode], sizeof(zones));
}


boolean LoadZonesPow(uchar  ibMonth, uchar  ibMode) {
	return LoadBuff(wFLA_ZONES_POW + ibMonth*bMODES + ibMode, &mpzoPowMonthMode[ibMonth][ibMode], sizeof(zones));
}



boolean SaveZonesEng(uchar  ibMonth, uchar  ibMode) {
	return SaveBuff(wFLA_ZONES_ENG + ibMonth*bMODES + ibMode, &mpzoEngMonthMode[ibMonth][ibMode], sizeof(zones));
}


boolean LoadZonesEng(uchar  ibMonth, uchar  ibMode) {
	return LoadBuff(wFLA_ZONES_ENG + ibMonth*bMODES + ibMode, &mpzoEngMonthMode[ibMonth][ibMode], sizeof(zones));
}



void    InitTariffs(void)
{
uchar  ibMonth, ibMode;

  LoadFile(&flPublicTariffs);
  LoadFile(&flOldTariffsMode);

  for (ibMonth=0; ibMonth<12-1; ibMonth++)
  {
    for (ibMode=0; ibMode<bMODES; ibMode++)
    {
    	LoadZonesPow(ibMonth, ibMode);
    	LoadZonesEng(ibMonth, ibMode);
    }
  }

  if (enGlobal == GLB_WORK)
  {
  	MakeAllCurrTariffs();
  }
  else
  {
  	memset(&mpchPowMonth, 0, sizeof(mpchPowMonth));
    memset(&mpchEngMonth, 0, sizeof(mpchEngMonth));
  }
}


void    ResetTariffs(void)
{
  fPublicTariffsCurr = false;
  SaveFile(&flPublicTariffs);

  bOldTariffsMode = 0;
  SaveFile(&flOldTariffsMode);

  DefaultTariffs();
}



void    SetZonePowMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  mpzoPowMonthMode[ibMonth][ibMode] = *pzoT;
  SaveZonesPow(ibMonth, ibMode);
}


zones  *PGetZonePowMonthMode(uchar ibMonth, uchar ibMode) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  return( &mpzoPowMonthMode[ibMonth][ibMode] );
}



void    SetZoneEngMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  mpzoEngMonthMode[ibMonth][ibMode] = *pzoT;
  SaveZonesEng(ibMonth, ibMode);
}


zones  *PGetZoneEngMonthMode(uchar ibMonth, uchar ibMode) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  return( &mpzoEngMonthMode[ibMonth][ibMode] );
}



// записывает суточный тарифный график на несколько мес€цев (дл€ энергии)
void    SetZonesEngMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT)
{
uchar  ibMonth;

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
    SetZoneEngMonthMode(ibMonth, ibMode, pzoT);
  }
}


// записывает суточный тарифный график на несколько мес€цев (дл€ мощности)
void    SetZonesPowMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT)
{
uchar  ibMonth;

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
    SetZonePowMonthMode(ibMonth, ibMode, pzoT);
  }
}



void    DefaultTariffs(void)
{
uchar  chOldMode;

  if (fPublicTariffsCurr == true)
  {
    chOldMode = '_';

    SetKeyZonePow();
    SetCharEngMonths(0,11,&zoKey,chOldMode);

    SetKeyZonePow();
    SetCharPowMonths(0,11,&zoKey,chOldMode);
  }
  else
  {
    chOldMode = '_';

    SetKeyZoneEng();
    SetCharEngMonths(0,11,&zoKey,chOldMode);

    SetKeyZonePow();
    SetCharPowMonths(0,11,&zoKey,chOldMode);
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



// возвращает тип текущих суток относительнос приска праздников
uchar   RelaxIndex(void)
{
uchar i;

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);
    if ((tiRelax.bDay   == tiAlt.bDay) &&
        (tiRelax.bMonth == tiAlt.bMonth)) 
      return tiRelax.bSecond;   
  }

  return 0;
}
// требует предварительной установки переменных tiAlt



// рассчитывает массив индексов тарифов дл€ каждого получаса текущих суток (дл€ мощности и энергии)
void    MakeAllCurrTariffs(void)
{
uchar  i, j;
uchar  ibMonth, ibMode;

  tiAlt = *PGetCurrTimeDate();

  if (boGapsFlag == false) 
  {
    ibMonth = tiAlt.bMonth - 1;
  }
  else
  {
    MakeGaps();
    ibMonth = mpbGaps[GetDayIndex_Alt()];
  } 

  ibMode  = GetModeAlt();               

  zoAlt = *PGetZoneEngMonthMode(ibMonth,ibMode);
  MakeTariff(mpibEngCurrTariff);

  zoAlt = *PGetZonePowMonthMode(ibMonth,ibMode);
  MakeTariff(mpibPowCurrTariff);

  if (boRelaxsFlag == true)
  {
    j = RelaxIndex();
    i = Weekday();
    if ((j != 2) && ((i == 5) || (i == 6) || (j == 1)))
    {
      i = ibRelaxsTariff; 
      if (i >= bTARIFFS) i = 0;
      // memset(&mpibEngCurrTariff, i, sizeof(mpibEngCurrTariff));
      memset(&mpibPowCurrTariff, i, sizeof(mpibPowCurrTariff));
    }
  }
}


void    MakeAllPrevTariffs(void)
{
uchar  i, j;
uchar  ibMonth, ibMode;

  ibMonth = tiAlt.bMonth - 1;                   

  if (boGapsFlag == false) 
  {
    ibMonth = tiAlt.bMonth - 1;
  }
  else
  {
    MakeGaps();
    ibMonth = mpbGaps[GetDayIndex_Alt()];
  } 

  ibMode  = GetModeAlt();               

  zoAlt = *PGetZoneEngMonthMode(ibMonth,ibMode);
  MakeTariff(mpibEngPrevTariff);

  zoAlt = *PGetZonePowMonthMode(ibMonth,ibMode);
  MakeTariff(mpibPowPrevTariff);

  if (boRelaxsFlag == true)
  {
    j = RelaxIndex();
    i = Weekday();
    if ((j != 2) && ((i == 5) || (i == 6) || (j == 1)))
    {
      i = ibRelaxsTariff; 
      if (i >= bTARIFFS) i = 0;
      // memset(&mpibEngPrevTariff, i, sizeof(mpibEngPrevTariff));
      memset(&mpibPowPrevTariff, i, sizeof(mpibPowPrevTariff));
    }
  }
}
// требует предварительной установки переменной tiAlt
