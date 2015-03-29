/*------------------------------------------------------------------------------
MEM_DIRECT.H


------------------------------------------------------------------------------*/

extern  time                    mptiEsc_T[bCANALS];

extern  real                    mpreEsc_S[bCANALS];

extern  time                    mptiEsc_S[bCANALS];

extern  real                    mpreEsc_V[bCANALS];

extern  time                    mptiEsc_V[bCANALS];



extern  moment                  moAlt;

extern  moment                  mpmoEsc_U[bCANALS];



extern  uint                    mpcwEscV_OK[bCANALS], mpcwEscV_Error[bCANALS],
                                mpcwEscS_OK[bCANALS], mpcwEscS_Error[bCANALS],
                                mpcwEscU_OK[bCANALS], mpcwEscU_Error[bCANALS];

extern  boolean                 mpboDefEscV[bCANALS],
                                mpboDefEscS[bCANALS],
                                mpboDefEscU[bCANALS];

extern  boolean                 boDisableEsc1, boDisableEsc2, boDisableEsc3;
