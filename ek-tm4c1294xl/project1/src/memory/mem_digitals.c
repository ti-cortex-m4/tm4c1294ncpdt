/*------------------------------------------------------------------------------
MEM_DIGITALS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// битовая маска используемых цифровых счётчиков
uint                    wDigitalsMask;

// массив разрешенных каналов
boolean                 mpboEnblCan[bCANALS];



// флаг использования паролей счётчиков
boolean                 boEnableKeys;

// массив паролей счётчиков
phone                   mpphKeys[bCANALS];



// цифровой счётчики
digital                 diPrev, diCurr;



// глобальная переменная
combo                   coEnergy;

// массив признаков для исключения повторного опроса
boolean                 mpboChannelsA[bCHANNELS];

// промежуточные массивы
ulong                   mpdwChannelsA[bCHANNELS],
                        mpdwChannelsB[bCHANNELS];

// промежуточные массивы
real                    mpreChannelsA[bCHANNELS],
                        mpreChannelsB[bCHANNELS];

// промежуточная переменная
time                    tiChannelC;



//
boolean                 boEnblCurrent, boEnblProfile;

//
uchar                   bTimeoutCurrent, bTimeoutProfile;



// массив признаков для исключения повторного опроса каналов, принадлежащих одному цифорвому счётчику
uchar                   mpboReadyCan[bCANALS];
