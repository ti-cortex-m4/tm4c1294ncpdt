/*------------------------------------------------------------------------------
MEM_EXTENDED_1.H


------------------------------------------------------------------------------*/

extern  real                    mpreEsc_S[bCANALS];

extern  time                    mptiEsc_S[bCANALS];

extern  real                    mpreEsc_V[bCANALS];

extern  time                    mptiEsc_V[bCANALS];

extern  time                    mptiEsc_U1[bCANALS];

extern  time                    mptiEsc_U2[bCANALS];



extern  uint                    mpcwEscV_OK[bCANALS], mpcwEscV_Error[bCANALS],
                                mpcwEscS_OK[bCANALS], mpcwEscS_Error[bCANALS],
                                mpcwEscU_OK[bCANALS], mpcwEscU_Error[bCANALS];

extern  bool                 mpboDefEscV[bCANALS],
                                mpboDefEscS[bCANALS],
                                mpboDefEscU[bCANALS];



extern  bool                 boDsblEscU, boDsblEscV, boDsblEscS;

extern  bool                 boMntEscS;

extern  bool                 boExtendedEscU, boExtendedEscV, boExtendedEscS;

