/*------------------------------------------------------------------------------
MEM_DEVICE_P!C


------------------------------------------------------------------------------*/

#include "../main.h"



// буфера для расшифровки пароля
uchar                   mpbPasswordEls[8], mpbRandomEls[16], mpbResultEls[16];

// буфера
uchar                   mpbEls1[8], mpbEls2[16];

// буфер профилей
uchar                   mpbBuffEls[128];

// переменные
uchar                   pbPutEls, pbGetEls, cbSizeEls;

// переменные
uchar                   bFlagElsCurr, bFlagElsPrev;

// переменные
uchar                   bCodeElsCurr, bCodeElsPrev;

// переменные
ulong                   dwStampElsCurr, dwStampElsPrev;

// переменные
uchar                   bBreakEls, bFirstEls;

// переменные
uchar                   mpbMappingEls[4];

// переменные
double                  mpdbChannelsEls[4];

// признак получаса перевода времени
bool                    boTimeChangeP;

// ???, индекс текущего получаса, индекс получаса перевода времени
ulong                   dwHouIndexP, dwHouIndexP1, dwHouIndexP2;

// массив мгновенных значений (напряжения по фазам)
float                   mpreParamP[3];

// счетчик времени
uint                    cwSecondLockoutP;
