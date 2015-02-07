/*------------------------------------------------------------------------------
MEM_TARIFFS.S

 TODO add requests for tariffs for all modes
------------------------------------------------------------------------------*/

#include        "../main.h"



// массив праздников
relaxs                  mpreRelaxs;

// внутренн€€ переменна€
time                    tiRelax;

// признак использовани€ праздников
boolean                 boRelaxsFlag;

// глобальна€ переменна€
uchar                   ibRelaxsTariff;



// массив суточных тарифных графиков по мес€цам и режимам работы (дл€ мощности и энергии)
zones                   mpzoPowMonthMode[12][bMODES],
                        mpzoEngMonthMode[12][bMODES];

// массив индексов тарифов дл€ каждого получаса текущих суток (дл€ мощности и энергии)
uchar                   mpibPowCurrTariff[48],
                        mpibEngCurrTariff[48];

// массив индексов тарифов дл€ каждого получаса текущих суток
uchar                   mpibPowPrevTariff[48],
                        mpibEngPrevTariff[48];

// признак совмещЄнных/раздельных суточных тарифных графиков за текущий и предыдущий мес€цы
boolean                 fPublicTariffsCurr,
                        fPublicTariffsPrev;



// массив символов задани€ тарифных зон по блока и мес€цам (старый вариант)
uchar                   mpcPowMonth[12],
                        mpcEngMonth[12];

// правило обработки тарифов в выходные дни (старый вариант)
uchar                   bTariffsMode;



// суточные тарифные графики
zones                   zoAlt,zoKey;

// изломы суточных тарифных графиков
breaks                  brAlt,brKey;



// флаг использовани€ тарифных периодов
boolean                 boGapsFlag;

// массив изломов тарифных периодов
gaps                    mpgaGaps;

// переменна€
time                    tiGap;

// график тарифных периодов за год по суткам
uchar                   mpbGaps[365];
