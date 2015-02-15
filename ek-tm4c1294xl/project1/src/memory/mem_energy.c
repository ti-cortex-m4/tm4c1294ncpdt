/*------------------------------------------------------------------------------
MEM_ENERGY.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// массивы накопленных импульсов (по текущим трЄмминутам)
uint                    mpwImpCurrMntCan[bCANALS];

// массивы накопленных импульсов (по трЄм минутам и получасам)
uint                    mpwImpMntCan[bMINUTES][bCANALS],
                        mpwImpHouCan[2][bCANALS];

// массивы накопленных импульсов по тарифам (по суткам, мес€цам и всего)
impulse                 mpimDayCan[2][bCANALS],
                        mpimMonCan[2][bCANALS],
                        mpimAbsCan[bCANALS];

// глобальна€ переменна€
impulse                 imAlt;

// массив показаний счЄтчиков на конец мес€ца
real                    mpreCntMonCan[2][bCANALS];

// массивы максимумов мощности по тарифам (по суткам и мес€цам)
power                   mppoDayGrp[2][bGROUPS],
                        mppoMonGrp[2][bGROUPS];
