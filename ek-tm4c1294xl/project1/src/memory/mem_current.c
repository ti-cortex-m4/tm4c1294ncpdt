/*------------------------------------------------------------------------------
MEM_CURRENT.C


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

// массив для хранения базовых значений всех каналов одного счетчика
ulong                   mpdwBaseDig[bCHANNELS];

// массивы вспомогательных переменных
uint                    mpwTrue[bCANALS],
                        mpwFalse[bCANALS],
                        mpwMore[bCANALS],
                        mpwLess[bCANALS],
                        mpwRepeat[bCANALS];



// массивы вспомогательных переменных
uint                    mpwMore100[bCANALS],
                        mpwMore1000[bCANALS],
                        mpwMore10000[bCANALS];

// массивы вспомогательных переменных
time                    mptiBaseOK[bCANALS],
                        mptiBaseError[bCANALS];
