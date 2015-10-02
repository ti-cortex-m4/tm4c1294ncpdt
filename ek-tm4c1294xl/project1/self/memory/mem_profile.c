/*------------------------------------------------------------------------------
MEM_PROFILE!C


------------------------------------------------------------------------------*/

#include "../main.h"



// флаг начала опроса 30-минутных графиков в ручном режиме
bool                    boManualProfile;

// счётчик принятых получасов
uint                    cwHouRead;

// длительность получасового опроса
uint                    cwHouLength;

// счётчики событий
uint                    mpcwProfile_OK[bCANALS],
                        mpcwProfile_Error[bCANALS],
                        mpcwDigital_OK[bCANALS],
                        mpcwCalcDig[bCANALS];

// признак коррекции времени при опросе цифровых счётчиков
bool                    fCurrCtrl;



// индекс на текущий интервал данных, хранимой в цифровых счётчиках
uint                    iwDigHou;

// количество интервалов данных, хранимых в цифровых счётчиках
uint                    cwDigHou;

// количество интервалов данных, хранимых в цифровых счётчиках
uchar                   cbDigDay, cbDigMon;



// адреса заголовков и адреса блоков данных: текущие и последние прочитанные
uint                    wBaseCurr, wOffsCurr,
                        wBaseLast;

// указатель
ulong                   dwBaseCurr;

// индекс получаса текущей записи
uchar                   bCurrHouIndex;



// глобальная переменная
uchar                   ibMinor, ibMinorMax;

// глобальная переменная
uint                    iwMajor;



// разница времени сумматора и счётчика
uchar                   bDeltaOld, bDeltaNew;



// байты в составе передаваемого запроса
uchar                   bOutputC0, bOutputC1, bOutputC2;

// счетчикм событий
uint                    mpcwOutputZ[bCANALS],
                        mpcwOutputC[bCANALS],
                        mpcwOutput0[bCANALS],
                        mpcwOutput1[bCANALS],
                        mpcwOutput2[bCANALS],
                        mpcwOutput3[bCANALS];

// глобальная переменная
time                    tiValueA, tiValueB, tiValueC, tiValueS;

// глобальная переменная
ulong                   dwValueC, dwValueS;



// промежуточный массив
float                   mpflBuffCanHou[4][48];

// промежуточный массив
float                   mpflEngFrac[bCANALS];

// промежуточный массив
float                   mpflEngFracDigCan[bCANALS][6];

// счетчики переполнений получасовых графиков
uint                    mpcwOverflowHhr[bCANALS];

// счетчики ошибок связи
uint                    mpcwErrorLink[bCANALS];

// делитель для энергии счетчика СЕ102
uint                    wDividerS;



// счетчики
uint                    mpcwProfileLinkWrn[bPORTS][48],
                        mpcwProfileLinkErr[bPORTS][48];
