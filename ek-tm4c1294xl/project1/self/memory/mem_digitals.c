/*------------------------------------------------------------------------------
MEM_DIGITALS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// битовая маска используемых цифровых счётчиков
uint                    wDigitalsMask;

// массив разрешенных каналов
bool                    mpboEnblCan[bCANALS];



// флаг использования паролей счётчиков
bool                    boEnblKeys;

// массив паролей счётчиков
line                    mpphKeys[bCANALS];

// дополнительные параметры цифровых счётчиков
ulong                   mpdwAddress1[bCANALS],
                        mpdwAddress2[bCANALS];



// цифровой счётчики
digital                 diPrev, diCurr, diNext, diLast;



// глобальная переменная
combo32                 coEnergy;

// массив признаков для исключения повторного опроса
bool                    mpboChannelsA[bCHANNELS];

// промежуточные массивы
ulong                   mpdwChannelsA[bCHANNELS],
                        mpdwChannelsB[bCHANNELS];

// промежуточный массив
double                  mpdbChannelsC[bCHANNELS];

// промежуточная переменная
time                    tiChannelC;



// флаги разрешения опроса трехминутных и получасовых графиков
bool                    boEnblCurrent, boEnblProfile;

// таймайты начала опроса трехминутных и получасовых графиков
uchar                   bTimeoutCurrent, bTimeoutProfile;

// флаг раздельного опроса нескольких каналов одного цифрового счётчика
bool                    boSeparateCan;

// флаг выдачи информации для пользователя/администратора
bool                    boShowMessages;

// флаг сокращенного вывода сообщений
bool                    boHideMessages;

// флаг коррекции времени цифровых счётчиков
bool                    boControlTime;

// флаг установки времени цифоровых счётчиков
bool                    boManageTime;



// массив признаков для исключения повторного опроса каналов, принадлежащих одному цифровому счётчику
uchar                   mpboReadyCan[bCANALS];



// счетчикм событий
uint                    mpcwFailure2[bCANALS];



// уровень доступа к счетчику Меркурий-230
uchar                   bKeysLevelB;

// флаг чтения профилей счетчика СС-301 (x6 - false, x1 - true)
bool                    boShortProfileC;
