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

