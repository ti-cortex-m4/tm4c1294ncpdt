/*------------------------------------------------------------------------------
MEM_ENERGY_SPEC.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// индекс на текущий интервал данных, хранимой в цифровых счЄтчиках
uint                    iwDigHou;

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



// массив счЄтчиков дл€ обработки перехода на зимнее врем€
uchar                   mpbWinterCan[bCANALS];



// количество каналов в цифровом счЄтчике
uchar                   cbChannels;

// массив каналов в цифровом счЄтчике
uint                    mpwChannels[bCHANNELS];



// флаг наличи€ открытых буферов
uchar                   boOpenCalc;



// достоверность
impulse                 mpdeDayCan[bCANALS],
                        mpdeMonCan[bCANALS];

// достоверность
uint                    mpwImpHouCanDef[bCANALS];



// массив брака по дн€м и мес€цам
time                    mpdeDay[bDAYS],
                        mpdeMon[bMONTHS];
