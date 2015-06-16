/*------------------------------------------------------------------------------
MEM_EXTENDED_1,C


------------------------------------------------------------------------------*/

#include "../main.h"



// значения счетчиков текущие (на момент последнего получасового опроса)
double                  mpdbEsc_S[bCANALS];

// время обновления значений mpdbEsc_S
time                    mptiEsc_S[bCANALS];

// значения счетчиков на начало текущих суток (на момент последнего получасового опроса)
double                  mpdbEsc_V[bCANALS];

// время обновления значений mpdbEsc_V
time                    mptiEsc_V[bCANALS];

// время цифровых счетчиков (на момент последнего получасового опроса)
time                    mptiEsc_U1[bCANALS];

// время обновления значений mpdbEsc_U1
time                    mptiEsc_U2[bCANALS];



// счётчики успешных опросов
uint                    mpcwEscV_OK[bCANALS],
                        mpcwEscS_OK[bCANALS],
                        mpcwEscU_OK[bCANALS];

// счётчики ошибочных опросов
uint                    mpcwEscV_Error[bCANALS],
                        mpcwEscS_Error[bCANALS],
                        mpcwEscU_Error[bCANALS];



// флаги запрета опросов
bool                    boDsblEscU, boDsblEscV, boDsblEscS;

//
bool                    boMntEscS;

//
bool                    boExtendedEscU, boExtendedEscV, boExtendedEscS;
