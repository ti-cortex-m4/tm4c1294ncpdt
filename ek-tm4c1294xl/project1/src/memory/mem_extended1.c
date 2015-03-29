/*------------------------------------------------------------------------------
MEM_DIRECT.C


------------------------------------------------------------------------------*/

#include        "../main.h"



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
