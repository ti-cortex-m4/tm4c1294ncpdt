/*------------------------------------------------------------------------------
MEM_CURRENT.C


------------------------------------------------------------------------------*/

#include "../main.h"



// массив базовых величин (в импульсах)
ulong                   mpdwBase[bCANALS];

// массив базовых величин (в плавающем формате)
real                    mpreBase[bCANALS];

// массив времени/даты обновления базовых величин
time                    mptiBase[bCANALS];

// массив флагов установки базовых величин
bool                    mpboBase[bCANALS];

// массив для хранения базовых значений всех каналов одного счетчика
ulong                   mpdwBaseDig[bCHANNELS];

// массив времени/даты счётчиков
time                    mptiOffs[bCANALS];

// глобальная переменная
time                    tiOffs;

// массивы вспомогательных переменных
uint                    mpwTrue[bCANALS],
                        mpwFalse[bCANALS],
                        mpwOverflow[bCANALS],
                        mpwUnderflow[bCANALS],
                        mpwRepeat[bCANALS];



// массивы вспомогательных переменных
uint                    mpwMore100[bCANALS],
                        mpwMore1000[bCANALS],
                        mpwMore10000[bCANALS];

// массивы вспомогательных переменных
time                    mptiBaseOK[bCANALS],
                        mptiBaseError[bCANALS];



// флаг первого запуска
bool                    boCurrent2;

// битовые маски каналов
uchar                   mpbCurrent2Curr[8],
                        mpbCurrent2Prev[8],
                        mpbCurrent2Buff[8];

// разрешения перерасчета
bool                    boEnblCurrent2;

// счетчики интервалов перерасчета
uint                    mpwCurrent2Mnt[bCANALS];

// счетчики переполнения
uint                    mpwCurrent2Overflow[bCANALS];
