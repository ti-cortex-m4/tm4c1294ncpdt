/*------------------------------------------------------------------------------
MEM_ENERGY!C


------------------------------------------------------------------------------*/

#include "../main.h"



// массивы накопленных импульсов (по текущим трЄмминутам)
uint                    mpwImpMntCanCurr[bCANALS];

// массивы накопленных импульсов (по трЄмминутам) TODO volatile
uint                    mpwImpMntCan[2][bCANALS];

// массивы накопленных импульсов (по получасам)
uint                    mpwImpHouCan[2][bCANALS];

// массивы накопленных импульсов по тарифам (по суткам, мес€цам и всего)
impulse                 mpimDayCan[2][bCANALS],
                        mpimMonCan[2][bCANALS],
                        mpimAbsCan[bCANALS];

// глобальна€ переменна€
impulse                 imAlt;

// массив показаний счЄтчиков на конец мес€ца
double                  mpdbCntMonCan[2][bCANALS];

// массивы максимумов мощности по тарифам (по суткам и мес€цам)
power                   mppoDayGrp[2][bGROUPS],
                        mppoMonGrp[2][bGROUPS];
