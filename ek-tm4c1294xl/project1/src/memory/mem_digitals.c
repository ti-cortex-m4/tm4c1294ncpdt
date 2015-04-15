/*------------------------------------------------------------------------------
MEM_DIGITALS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// битовая маска используемых цифровых счётчиков
uint                    wDigitalsMask;

// массив разрешенных каналов
boolean                 mpboEnblCan[bCANALS];



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
combo32                 coEnergy;

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

// флаг коррекции времени цифровых счётчиков
boolean                 boControlTime;

// флаг установки времени цифоровых счётчиков
boolean                 boManageTime;



// массив признаков для исключения повторного опроса каналов, принадлежащих одному цифровому счётчику
uchar                   mpboReadyCan[bCANALS];



// счетчикм событий
uint                    mpcwFailure2[bCANALS];



// уровень доступа к счетчику Меркурий-230
uchar                   bKeysLevelB;

// флаг чтения профилей счетчика СС-301 (x6 - false, x1 - true)
boolean                 boShortProfileC;

// флаг
boolean                 boDirectCntD;
