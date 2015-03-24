/*------------------------------------------------------------------------------
MEM_ENERGY_SPEC.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// массивы накопленных импульсов (по получасам)
uint                    mpwImpHouCanSpec[bCANALS];

// массивы накопленных импульсов по тарифам (по суткам и мес€цам)
impulse                 mpimDayCanSpec[bCANALS],
                        mpimMonCanSpec[bCANALS];

// массивы максимумов мощности по тарифам (по суткам и мес€цам)
power                   mppoDayGrpSpec[bGROUPS],
                        mppoMonGrpSpec[bGROUPS];



// врем€/дата данных в специальных буферах
time                    tiOldDay, tiOldMon;

// индексы данных в специальных буферах
uchar                   ibOldDay, ibOldMon;



// флаг наличи€ открытых буферов
uchar                   boOpenCalc;
