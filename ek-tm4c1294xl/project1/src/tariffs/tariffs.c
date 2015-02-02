/*------------------------------------------------------------------------------
TARIFFS.C

 Подпрограммы управления тарифами
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../display.h"
#include        "../delay.h"
#include        "../access.h"
#include        "../rtc.h"
#include        "../timedate.h"
#include        "zones.h"
#include        "oldtariffs.h"
#include        "relaxs.h"
#include        "gaps.h"



// текущие индексы по массивам
uchar                   ibMonth,ibMode;



// записывает факт задания суточного тарифного графика (для энергии)
void    SetBoolEngMonthMode(void)
{
  mpboEngMonthMode[ibMonth][ibMode] = boAlt;
}

/*
// читает факт задания суточного тарифного графика (для энергии)
boolean GetBoolEngMonthMode(void)
{
  return( mpboEngMonthMode[ibMonth][ibMode] );
}
*/

// записывает факт задания суточного тарифного графика (для мощности)
void    SetBoolPowMonthMode(void)
{
  mpboPowMonthMode[ibMonth][ibMode] = boAlt;
}

/*
// читает факт задания суточного тарифного графика (для мощности)
boolean GetBoolPowMonthMode(void)
{
  return( mpboPowMonthMode[ibMonth][ibMode] );
}
*/


// записывает суточный тарифный график (для энергии)
void    SetZoneEngMonthMode(void)
{
  mpzoEngMonthMode[ibMonth][ibMode] = zoAlt;
}


// читает суточный тарифный график (для энергии)
zones  *PGetZoneEngMonthMode(void)
{
  return( &mpzoEngMonthMode[ibMonth][ibMode] );
}


// записывает суточный тарифный график (для мощности)
void    SetZonePowMonthMode(void)
{
  mpzoPowMonthMode[ibMonth][ibMode] = zoAlt;
}


// читает суточный тарифный график (для мощности)
zones  *PGetZonePowMonthMode(void)
{
  return( &mpzoPowMonthMode[ibMonth][ibMode] );
}



// записывает суточный тарифный график на несколько месяцев (для энергии)
void    SetZonesEngMonthsMode(uchar  ibBeg, uchar  ibEnd)
{
  boAlt = true;
  memcpy(&zoAlt, &zoKey, sizeof(zones));

  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    SetZoneEngMonthMode();
    SetBoolEngMonthMode();
  }
}
// требует предварительной установки переменных ibMode,zoKey


// записывает суточный тарифный график на несколько месяцев (для мощности)
void    SetZonesPowMonthsMode(uchar  ibBeg, uchar  ibEnd)
{
  boAlt = true;
  memcpy(&zoAlt, &zoKey, sizeof(zones));

  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    SetZonePowMonthMode();
    SetBoolPowMonthMode();
  }
}
// требует предварительной установки переменных ibMode,zoKey



void    SetTariffsDefault(void)
{
  if (boPublicCurr == true)
  {
    chOldMode = '_';

    SetKeyZonePow();
    SetCharEngMonths(0,11);

    SetKeyZonePow();
    SetCharPowMonths(0,11);
  }
  else
  {
    chOldMode = '_';

    SetKeyZoneEng();
    SetCharEngMonths(0,11);

    SetKeyZonePow();
    SetCharPowMonths(0,11);
  }
}



// сброс настроек по умолчанию
void    ResetTariffs(void)
{
  // совмещённые тарифные графики для мщности и энергии
  boPublicCurr = false;

  // старый вариант обработки тарифов
  boOldTariffs = true;

  // правило обработки тарифов в выходные дни (старый вариант)
  bOldMode = 0;

  boAlt = false;
  for (ibMonth=0; ibMonth<12+4+1; ibMonth++)
  {
    for (ibMode=0; ibMode<bMODES; ibMode++)
    {
      SetBoolEngMonthMode(); 
      SetBoolPowMonthMode(); 
    }
  }

  memset(&mpchEngMonth, '\0', sizeof(mpchEngMonth)); 
  memset(&mpchPowMonth, '\0', sizeof(mpchPowMonth)); 

  SetTariffsDefault();
}



// рассчитывает массив индексов тарифов для каждого получаса текущих суток
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



// рассчитывает массив индексов тарифов для каждого получаса текущих суток (для мощности и энергии)
void    MakeAllCurrTariffs(void)
{
uchar  i,j;

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

  zoAlt = *PGetZoneEngMonthMode();
  MakeTariff(mpibEngCurrTariff);

  zoAlt = *PGetZonePowMonthMode();
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
uchar  i,j;

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

  zoAlt = *PGetZoneEngMonthMode();
  MakeTariff(mpibEngPrevTariff);

  zoAlt = *PGetZonePowMonthMode();
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
