/*------------------------------------------------------------------------------
MEM_DIGITALS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// битовая маска используемых цифровых счётчиков
uint                    wDigitalsMask;

// массив разрешенных каналов
boolean                 mpboEnblCan[bCANALS];

//  график опроса цифровых счётчиков по портам и получасам
boolean                 mpboEnblPrtHou[bPORTS][48];

//  график коррекции времени цифровых счётчиков по получасам
boolean                 mpboCtrlHou[48];



// флаг использования паролей счётчиков
boolean                 boEnblKeys;

// массив паролей счётчиков
phone                   mpphKeys[bCANALS];

// дополнительные параметры цифровых счётчиков
ulong                   mpdwAddress1[bCANALS],
                        mpdwAddress2[bCANALS];



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

// флаг выдачи информации для пользователя/администратора
boolean                 boShowMessages;

// флаг сокращенного вывода сообщений
boolean                 boHideMessages;



// массив признаков для исключения повторного опроса каналов, принадлежащих одному цифровому счётчику
uchar                   mpboReadyCan[bCANALS];



// счетчикм событий
uint                    mpcwFailure2[bCANALS];
