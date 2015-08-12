/*------------------------------------------------------------------------------
MEM_PHONES.C


------------------------------------------------------------------------------*/

#include "../main.h"



// массив номеров телефонов
line                    mpphPhones[bCANALS];

// максимальное время ожидания сигнала Connect
uchar                   bMaxConnect;

// флаг управления модемом: настройки 2
bool                    boCustomModem;

// счётчики для контроля работы модемной связи
uint                    mpcwBaud[bPORTS],
                        mpcwCommon[bPORTS],
                        mpcwCustom[bPORTS],
                        mpcwConnect[bPORTS],
                        mpcwEscape[bPORTS],
                        mpcwHookOff[bPORTS],
                        mpcwDTROff[bPORTS];
