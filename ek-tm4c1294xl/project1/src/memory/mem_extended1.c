/*------------------------------------------------------------------------------
MEM_DIRECT.C


------------------------------------------------------------------------------*/

#include        "../main.h"



//
time                    mptiEsc_T[bCANALS];

//
real                    mpreEsc_S[bCANALS];

//
time                    mptiEsc_S[bCANALS];

//
real                    mpreEsc_V[bCANALS];

//
time                    mptiEsc_V[bCANALS];



// глобальная переменная
moment                  moAlt;

// массив переменных moment для расширенного опроса цифровых счётчиков
moment                  mpmoEsc_U[bCANALS];



// счётчики событий
uint                    mpcwEscV_OK[bCANALS], mpcwEscV_Error[bCANALS],
                        mpcwEscS_OK[bCANALS], mpcwEscS_Error[bCANALS],
                        mpcwEscU_OK[bCANALS], mpcwEscU_Error[bCANALS];

// признаки брака непосредственных показаний
boolean                 mpboDefEscV[bCANALS],
                        mpboDefEscS[bCANALS],
                        mpboDefEscU[bCANALS];

// флаги запрета опроса показаний
boolean                 boDisableEsc1, boDisableEsc2, boDisableEsc3;
