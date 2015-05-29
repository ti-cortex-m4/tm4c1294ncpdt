/*------------------------------------------------------------------------------
MEM_EXTENDED_1.C


------------------------------------------------------------------------------*/

#include "../main.h"



//
double                  mpdbEsc_S[bCANALS];

//
time                    mptiEsc_S[bCANALS];

//
double                  mpdbEsc_V[bCANALS];

//
time                    mptiEsc_V[bCANALS];

//
time                    mptiEsc_U1[bCANALS];

//
time                    mptiEsc_U2[bCANALS];



// счётчики событий
uint                    mpcwEscV_OK[bCANALS], mpcwEscV_Error[bCANALS],
                        mpcwEscS_OK[bCANALS], mpcwEscS_Error[bCANALS],
                        mpcwEscU_OK[bCANALS], mpcwEscU_Error[bCANALS];

// признаки брака непосредственных показаний
bool                    mpboDefEscV[bCANALS],
                        mpboDefEscS[bCANALS],
                        mpboDefEscU[bCANALS];



// флаги запрета опроса показаний
bool                    boDsblEscU, boDsblEscV, boDsblEscS;

// флаг
bool                    boMntEscS;

// флаг специальной подготовки данных для Esc-запросов
bool                    boExtendedEscU, boExtendedEscV, boExtendedEscS;
