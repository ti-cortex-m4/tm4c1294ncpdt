/*------------------------------------------------------------------------------
MEM_TARIFFS.S

 TODO add requests for tariffs for all modes
------------------------------------------------------------------------------*/

#include "../main.h"



// признак использовани€ праздников
boolean                 boRelaxsFlag;

// тариф при использовании праздников
uchar                   ibRelaxsTariff;

// массив праздников
relaxs                  reRelaxs;

// глобальна€ переменна€
time                    tiRelax;



// массив суточных тарифных графиков по мес€цам и режимам работы (дл€ мощности и энергии)
zone                    mpzoPowMonthMode[12][bMODES],
                        mpzoEngMonthMode[12][bMODES];

// массив индексов тарифов дл€ каждого получаса текущих суток (дл€ мощности и энергии)
uchar                   mpibPowCurrTariff[48],
                        mpibEngCurrTariff[48];

// массив индексов тарифов дл€ каждого получаса текущих суток
uchar                   mpibPowPrevTariff[48],
                        mpibEngPrevTariff[48];

// признак совмещЄнных/раздельных суточных тарифных графиков за текущий и предыдущий мес€цы
boolean                 fPublicTariffs;

// массив символов задани€ тарифных зон по блока и мес€цам (старый вариант)
period                  mpeTariffPow[12],
                        mpeTariffEng[12];

// правило обработки тарифов в выходные дни (старый вариант)
uchar                   bOldTrfMode;



// суточные тарифные графики
zone                    zoAlt, zoKey;

// изломы суточных тарифных графиков
br3ak                   brAlt, brKey;



// флаг использовани€ тарифных периодов
boolean                 boGapsFlag;

// массив изломов тарифных периодов
gaps                    gaGaps;

// переменна€
time                    tiGap;

// график тарифных периодов за год по суткам
uchar                   mpbGaps[365];
