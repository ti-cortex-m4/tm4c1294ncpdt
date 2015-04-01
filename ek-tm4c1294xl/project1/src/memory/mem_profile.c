/*------------------------------------------------------------------------------
MEM_PROFILE.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// флаг начала опроса 30-минутных графиков в ручном режиме
boolean                 boManualProfile;

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



// адреса заголовков и адреса блоков данных: текущие и последние прочитанные
uint                    wBaseCurr, wOffsCurr,
                        wBaseLast;

// указатель
ulong                   dwBaseCurr;



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
time                    tiValueC;

// глобальная переменная
ulong                   dwValueC;


