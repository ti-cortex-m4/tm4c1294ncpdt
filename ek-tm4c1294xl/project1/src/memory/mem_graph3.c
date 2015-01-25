/*------------------------------------------------------------------------------
MEM_GRAPH3.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// массив базовых величин (в импульсах)
ulong                   mpdwBase[bCANALS];

// массив базовых величин (в плавающем формате)
real                    mpreBase[bCANALS];

// массив времени/даты обновления базовых величин
time                    mptiBase[bCANALS];

// массив флагов установки базовых величин
boolean                 mpboBase[bCANALS];

// массивы вспомогательных переменных
uint                    mpwTrue[bCANALS],
                        mpwFalse[bCANALS],
                        mpwMore[bCANALS],
                        mpwLess[bCANALS],
                        mpwRepeat[bCANALS];
