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
digital                 diPrev, diCurr, diNext, diLast;



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



// флаги разрешения опроса трехминутных и получасовых графиков
boolean                 boEnblCurrent, boEnblProfile;

// таймайты начала опроса трехминутных и получасовых графиков
uchar                   bTimeoutCurrent, bTimeoutProfile;

// флаг раздельного опроса нескольких каналов одного цифрового счётчика
boolean                 boSeparateCan;

// флаг сокращенного вывода сообщений
boolean                 boHideMessages;



// массив признаков для исключения повторного опроса каналов, принадлежащих одному цифорвому счётчику
uchar                   mpboReadyCan[bCANALS];

// массив для хранения базовых значений всех каналов одного счетчика
ulong                   mpdwBaseDig[bCHANNELS];
