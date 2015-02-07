/*------------------------------------------------------------------------------
OLDTARIFFS.—

 ѕодпрограммы управлени€ тарифами (старый вариант)
------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../access.h"
#include        "tariffs.h"
#include        "zones.h"



// замен€ет во всех изломах переменной zoAlt один тариф на другой
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



// записывает в режим ibAltMode изменЄнный суточный тарифный график из режима 0 (будни)
void    ReplaceMode(uchar  ibMonth, uchar  ibMode, domain  doT, uchar  ibTariffOld, uchar  ibTariffNew)
{
  if (doT == DOM_POWER)
  {
    // читаем суточный тарифный график из режима 0 (будни)
    zoAlt = *PGetZonePowMonthMode(ibMonth, 0);

    // замен€ем один тариф на другой
    ReplaceZone(ibTariffOld,ibTariffNew);

    // записываем изменЄнный суточный тарифный график
    SetZonePowMonthMode(ibMonth, ibMode, &zoAlt);
  }
  else
  {
    // читаем суточный тарифный график из режима 0 (будни)
    zoAlt = *PGetZoneEngMonthMode(ibMonth, 0);

    // замен€ем один тариф на другой
    ReplaceZone(ibTariffOld,ibTariffNew);

    // записываем изменЄнный суточный тарифный график
    SetZoneEngMonthMode(ibMonth, ibMode, &zoAlt);
  }
}



// поддержка старого варианта обратотки тарифов в нерабочие дни
void    MakeTariffsModeMonth(uchar  ibMonth, domain  doT)
{
uchar  ibMode;

  switch (bTariffsMode)
  {     
    case 0:         
    	ibMode = 1;                          // дл€ суббот
      ReplaceMode(ibMonth,ibMode,doT,0,0); // одинаковые тарифы в рабочие и нерабочие дни
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,2);
      ReplaceMode(ibMonth,ibMode,doT,3,3);

      ibMode = 2;                          // дл€ выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,0); // одинаковые тарифы в рабочие и нерабочие дни
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,2);
      ReplaceMode(ibMonth,ibMode,doT,3,3);
      break;
    
    case 1:
    case 3:          
    	ibMode = 1;                          // дл€ суббот
      ReplaceMode(ibMonth,ibMode,doT,0,1); // в суботние и выходные дни по дневному тарифу
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,1);
      ReplaceMode(ibMonth,ibMode,doT,3,1);

      ibMode = 2;                          // дл€ выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,1); // в суботние и выходные дни по дневному тарифу
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,1);
      ReplaceMode(ibMonth,ibMode,doT,3,1);
      break;
    
    case 2:          
    	ibMode = 1;                          // дл€ суббот
      ReplaceMode(ibMonth,ibMode,doT,0,0); // в суботние и выходные дни по ночному тарифу
      ReplaceMode(ibMonth,ibMode,doT,1,0);
      ReplaceMode(ibMonth,ibMode,doT,2,0);
      ReplaceMode(ibMonth,ibMode,doT,3,0);

      ibMode = 2;                          // дл€ выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,0); // в суботние и выходные дни по ночному тарифу
      ReplaceMode(ibMonth,ibMode,doT,1,0);
      ReplaceMode(ibMonth,ibMode,doT,2,0);
      ReplaceMode(ibMonth,ibMode,doT,3,0);
      break;

    case 4:          
    	ibMode = 1;                          // дл€ суббот
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,0); // дневной тариф замен€етс€ на ночной тариф
      ReplaceMode(ibMonth,ibMode,doT,2,1); // утренний и вечерний тарифы замен€ютс€ на дневной тариф
      ReplaceMode(ibMonth,ibMode,doT,3,1);

      ibMode = 2;                          // дл€ выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,0); // дневной тариф замен€етс€ на ночной тариф
      ReplaceMode(ibMonth,ibMode,doT,2,1); // утренний и вечерний тарифы замен€ютс€ на дневной тариф
      ReplaceMode(ibMonth,ibMode,doT,3,1);
      break;

    case 5:          
    	ibMode = 1;                          // дл€ суббот
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,1); // утренний и вечерний тарифы замен€ютс€ на дневной тариф
      ReplaceMode(ibMonth,ibMode,doT,3,1);

      ibMode = 2;                          // дл€ выходных дней
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,0); // дневной тариф замен€етс€ на ночной тариф
      ReplaceMode(ibMonth,ibMode,doT,2,1); // утренний и вечерний тарифы замен€ютс€ на дневной тариф
      ReplaceMode(ibMonth,ibMode,doT,3,1);
      break;
  }
}



// изменение старого варианта обратотки тарифов в нерабочие дни
void    MakeTariffsMode(void)
{
uchar  ibMonth;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
  	MakeTariffsModeMonth(ibMonth, DOM_ENERGY);
  	MakeTariffsModeMonth(ibMonth, DOM_POWER);
  }
}



// запись суточного тарифного графика на несколько мес€цев (дл€ энергии)
void    SetCharEngMonths(uchar  ibMonthBeg, uchar  ibMonthEnd, zones  *pzoT, uchar  chOldMode)
{
uchar  ibMonth;

  SetZonesEngMonthsMode(ibMonthBeg, ibMonthEnd, 0, pzoT);

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
  	MakeTariffsModeMonth(ibMonth, DOM_ENERGY);
    mpchEngMonth[ibMonth] = chOldMode;
  }
}


// запись суточного тарифного графика на несколько мес€цев (дл€ мощности)
void    SetCharPowMonths(uchar  ibMonthBeg, uchar  ibMonthEnd, zones  *pzoT, uchar  chOldMode)
{
uchar  ibMonth;

  SetZonesPowMonthsMode(ibMonthBeg, ibMonthEnd, 0, pzoT);

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
  	MakeTariffsModeMonth(ibMonth, DOM_POWER);
    mpchPowMonth[ibMonth] = chOldMode;
  }
}
