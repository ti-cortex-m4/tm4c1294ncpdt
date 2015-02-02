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



bool                    fEnergy;



// заменяет во всех изломах переменной zoAlt один тариф на другой
void    ReplaceZone(uchar  ibOld, uchar  ibNew)
{
uchar  i;

  for (i=0; i<GetZoneAltSize(); i++)
  {
    GetZoneAltBreak(i);
    if (brAlt.ibTariff = ibOld)
    {
      brAlt.ibTariff = ibNew;
      SetZoneAltBreak(i);
    }
  }
}



// записывает в режим ibAltMode изменённый суточный тарифный график из режима 0 (будни)
void    ReplaceMode(uchar  ibOld, uchar  ibNew)
{
  if (fEnergy == 0)
  {
    // читаем суточный тарифный график из режима 0 (будни)
    ibMode = 0;
    zoAlt = *PGetZonePowMonthMode();

    // заменяем один тариф на другой
    ReplaceZone(ibOld,ibNew);                      

    // подготавливаем запись в режим ibAltMode
    ibMode = ibAltMode;
    boAlt = true;

    // записываем изменённый суточный тарифный график
    SetZonePowMonthMode();     
    SetBoolPowMonthMode();
  }
  else
  {
    // читаем суточный тарифный график из режима 0 (будни)
    ibMode = 0;
    zoAlt = *PGetZoneEngMonthMode();

    // заменяем один тариф на другой
    ReplaceZone(ibOld,ibNew);

    // подготавливаем запись в режим ibAltMode
    ibMode = ibAltMode;
    boAlt = true;

    // записываем изменённый суточный тарифный график
    SetZoneEngMonthMode();
    SetBoolEngMonthMode();
  }
}
// требует предварительной установки переменных ibMonth,ibAltMode



// поддержка старого варианта обратотки тарифов в нерабочие дни
void    MakeOldMode(void)
{
  switch (bOldMode)
  {     
    case 0:         
      ibAltMode = 1;    // для суббот
      ReplaceMode(0,0); // одинаковые тарифы в рабочие и нерабочие дни
      ReplaceMode(1,1);
      ReplaceMode(2,2);
      ReplaceMode(3,3);

      ibAltMode = 2;    // для выходных дней
      ReplaceMode(0,0); // одинаковые тарифы в рабочие и нерабочие дни
      ReplaceMode(1,1);
      ReplaceMode(2,2);
      ReplaceMode(3,3);
      break;
    
    case 1:
    case 3:          
      ibAltMode = 1;    // для суббот
      ReplaceMode(0,1); // в суботние и выходные дни по дневному тарифу
      ReplaceMode(1,1);
      ReplaceMode(2,1);
      ReplaceMode(3,1);

      ibAltMode = 2;    // для выходных дней
      ReplaceMode(0,1); // в суботние и выходные дни по дневному тарифу
      ReplaceMode(1,1);
      ReplaceMode(2,1);
      ReplaceMode(3,1);
      break;
    
    case 2:          
      ibAltMode = 1;    // для суббот
      ReplaceMode(0,0); // в суботние и выходные дни по ночному тарифу
      ReplaceMode(1,0);
      ReplaceMode(2,0);
      ReplaceMode(3,0);

      ibAltMode = 2;    // для выходных дней
      ReplaceMode(0,0); // в суботние и выходные дни по ночному тарифу
      ReplaceMode(1,0);
      ReplaceMode(2,0);
      ReplaceMode(3,0);
      break;

    case 4:          
      ibAltMode = 1;    // для суббот
      ReplaceMode(0,0);       
      ReplaceMode(1,0); // дневной тариф заменяется на ночной тариф
      ReplaceMode(2,1); // утренний и вечерний тарифы заменяются на дневной тариф
      ReplaceMode(3,1);

      ibAltMode = 2;    // для выходных дней
      ReplaceMode(0,0);       
      ReplaceMode(1,0); // дневной тариф заменяется на ночной тариф
      ReplaceMode(2,1); // утренний и вечерний тарифы заменяются на дневной тариф
      ReplaceMode(3,1);
      break;

    case 5:          
      ibAltMode = 1;    // для суббот
      ReplaceMode(0,0);       
      ReplaceMode(1,1);       
      ReplaceMode(2,1); // утренний и вечерний тарифы заменяются на дневной тариф
      ReplaceMode(3,1);

      ibAltMode = 2;    // для выходных дней
      ReplaceMode(0,0);       
      ReplaceMode(1,0); // дневной тариф заменяется на ночной тариф
      ReplaceMode(2,1); // утренний и вечерний тарифы заменяются на дневной тариф
      ReplaceMode(3,1);
      break;
  }
}
// требует предварительной установки переменных ibMonth,fEnergy



// изменение старого варианта обратотки тарифов в нерабочие дни
void    MakeAllOldModes(uchar  bT)
{
  bOldMode = bT;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
    fEnergy = 1; MakeOldMode();
    fEnergy = 0; MakeOldMode();
  }
}



// запись суточного тарифного графика на несколько месяцев (для энергии)
void    SetCharEngMonths(uchar  ibBeg, uchar  ibEnd)
{
  ibMode = 0;
  SetZonesEngMonthsMode(ibBeg,ibEnd);

  fEnergy = 1;
  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    MakeOldMode();
    mpchEngMonth[ibMonth] = chOldMode;
  }
}
// требует предварительной установки переменных zoKey,chOldMode


// запись суточного тарифного графика на несколько месяцев (для мощности)
void    SetCharPowMonths(uchar  ibBeg, uchar  ibEnd)
{
  ibMode = 0;
  SetZonesPowMonthsMode(ibBeg,ibEnd);

  fEnergy = 0;
  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    MakeOldMode();
    mpchPowMonth[ibMonth] = chOldMode;
  }
}
// требует предварительной установки переменных zoKey,chOldMode
