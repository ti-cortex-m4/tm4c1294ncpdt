/*------------------------------------------------------------------------------
OLDTARIFFS.С

 Подпрограммы управления тарифами (старый вариант)
------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../access.h"
#include        "tariffs.h"
#include        "zones.h"



// заменяет во всех изломах переменной zoAlt один тариф на другой
void    ReplaceZone(uchar  ibTariffOld, uchar  ibTariffNew)
{
uchar  i;

  for (i=0; i<GetZoneAltSize(); i++)
  {
    GetZoneAltBreak(i);
    if (brAlt.ibTariff = ibTariffOld)
    {
      brAlt.ibTariff = ibTariffNew;
      SetZoneAltBreak(i);
    }
  }
}



// записывает в режим ibAltMode изменённый суточный тарифный график из режима 0 (будни)
void    ReplaceMode(uchar  ibMonth, uchar  ibMode, domain  doT, uchar  ibTariffOld, uchar  ibTariffNew)
{
  if (doT == DOM_POWER)
  {
    // читаем суточный тарифный график из режима 0 (будни)
    zoAlt = *PGetZonePowMonthMode(ibMonth, 0);

    // заменяем один тариф на другой
    ReplaceZone(ibTariffOld,ibTariffNew);

    // записываем изменённый суточный тарифный график
    SetZonePowMonthMode(ibMonth, ibMode, &zoAlt);
    SetBoolPowMonthMode(ibMonth, ibMode, true);
  }
  else
  {
    // читаем суточный тарифный график из режима 0 (будни)
    zoAlt = *PGetZoneEngMonthMode(ibMonth, 0);

    // заменяем один тариф на другой
    ReplaceZone(ibTariffOld,ibTariffNew);

    // записываем изменённый суточный тарифный график
    SetZoneEngMonthMode(ibMonth, ibMode, &zoAlt);
    SetBoolEngMonthMode(ibMonth, ibMode, true);
  }
}



// поддержка старого варианта обратотки тарифов в нерабочие дни
void    MakeOldMode(uchar  ibMonth, domain  doT)
{
uchar  ibMode;

  switch (bOldMode)
  {     
    case 0:         
    	ibMode = 1;                      // для суббот
      ReplaceMode(ibMonth,ibMode,doT,0,0); // одинаковые тарифы в рабочие и нерабочие дни
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,2);
      ReplaceMode(ibMonth,ibMode,doT,3,3);

      ibMode = 2;                      // для выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,0); // одинаковые тарифы в рабочие и нерабочие дни
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,2);
      ReplaceMode(ibMonth,ibMode,doT,3,3);
      break;
    
    case 1:
    case 3:          
    	ibMode = 1;                      // для суббот
      ReplaceMode(ibMonth,ibMode,doT,0,1); // в суботние и выходные дни по дневному тарифу
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,1);
      ReplaceMode(ibMonth,ibMode,doT,3,1);

      ibMode = 2;                      // для выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,1); // в суботние и выходные дни по дневному тарифу
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,1);
      ReplaceMode(ibMonth,ibMode,doT,3,1);
      break;
    
    case 2:          
    	ibMode = 1;                      // для суббот
      ReplaceMode(ibMonth,ibMode,doT,0,0); // в суботние и выходные дни по ночному тарифу
      ReplaceMode(ibMonth,ibMode,doT,1,0);
      ReplaceMode(ibMonth,ibMode,doT,2,0);
      ReplaceMode(ibMonth,ibMode,doT,3,0);

      ibMode = 2;                      // для выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,0); // в суботние и выходные дни по ночному тарифу
      ReplaceMode(ibMonth,ibMode,doT,1,0);
      ReplaceMode(ibMonth,ibMode,doT,2,0);
      ReplaceMode(ibMonth,ibMode,doT,3,0);
      break;

    case 4:          
    	ibMode = 1;                      // для суббот
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,0); // дневной тариф заменяется на ночной тариф
      ReplaceMode(ibMonth,ibMode,doT,2,1); // утренний и вечерний тарифы заменяются на дневной тариф
      ReplaceMode(ibMonth,ibMode,doT,3,1);

      ibMode = 2;                      // для выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,0); // дневной тариф заменяется на ночной тариф
      ReplaceMode(ibMonth,ibMode,doT,2,1); // утренний и вечерний тарифы заменяются на дневной тариф
      ReplaceMode(ibMonth,ibMode,doT,3,1);
      break;

    case 5:          
    	ibMode = 1;                      // для суббот
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,1); // утренний и вечерний тарифы заменяются на дневной тариф
      ReplaceMode(ibMonth,ibMode,doT,3,1);

      ibMode = 2;                      // для выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,0); // дневной тариф заменяется на ночной тариф
      ReplaceMode(ibMonth,ibMode,doT,2,1); // утренний и вечерний тарифы заменяются на дневной тариф
      ReplaceMode(ibMonth,ibMode,doT,3,1);
      break;
  }
}
// требует предварительной установки переменных ibMonth,fEnergy



// изменение старого варианта обратотки тарифов в нерабочие дни
void    MakeAllOldModes(uchar  bT)
{
uchar  ibMonth;

  bOldMode = bT;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
    MakeOldMode(ibMonth, DOM_ENERGY);
    MakeOldMode(ibMonth, DOM_POWER);
  }
}



// запись суточного тарифного графика на несколько месяцев (для энергии)
void    SetCharEngMonths(uchar  ibMonthBeg, uchar  ibMonthEnd, zones *pzoT)
{
uchar  ibMonth;

  SetZonesEngMonthsMode(ibMonthBeg, ibMonthEnd, 0, pzoT);

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
    MakeOldMode(ibMonth, DOM_ENERGY);
    mpchEngMonth[ibMonth] = chOldMode;
  }
}
// требует предварительной установки переменных zoKey,chOldMode


// запись суточного тарифного графика на несколько месяцев (для мощности)
void    SetCharPowMonths(uchar  ibMonthBeg, uchar  ibMonthEnd, zones *pzoT)
{
uchar  ibMonth;

  SetZonesPowMonthsMode(ibMonthBeg, ibMonthEnd, 0, pzoT);

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
    MakeOldMode(ibMonth, DOM_POWER);
    mpchPowMonth[ibMonth] = chOldMode;
  }
}
// требует предварительной установки переменных zoKey,chOldMode
