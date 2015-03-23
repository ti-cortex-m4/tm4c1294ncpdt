/*------------------------------------------------------------------------------
MEM_PROFILE.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// флаг начала опроса 30-минутных графиков в ручном режиме
boolean                 boManualProfile;



// счётчики событий
uint                    mpcwEscV_OK[bCANALS], mpcwEscV_Error[bCANALS],
                        mpcwEscS_OK[bCANALS], mpcwEscS_Error[bCANALS],
                        mpcwEscU_OK[bCANALS], mpcwEscU_Error[bCANALS];

// счётчики событий
uint                    mpcwProfile_OK[bCANALS],
                        mpcwProfile_Error[bCANALS];

// признаки брака непосредственных показаний
boolean                 mpboDefEscV[bCANALS],
                        mpboDefEscS[bCANALS],
                        mpboDefEscU[bCANALS];
