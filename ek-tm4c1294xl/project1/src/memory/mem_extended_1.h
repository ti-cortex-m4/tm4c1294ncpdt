/*------------------------------------------------------------------------------
MEM_EXTENDED_1,H


------------------------------------------------------------------------------*/

extern  double                  mpdbEsc_S[bCANALS];

extern  time                    mptiEsc_S[bCANALS];

extern  double                  mpdbEsc_V[bCANALS];

extern  time                    mptiEsc_V[bCANALS];

extern  time                    mptiEsc_U1[bCANALS];

extern  time                    mptiEsc_U2[bCANALS];



extern  uint                    mpcwEscV_OK[bCANALS],
                                mpcwEscS_OK[bCANALS],
                                mpcwEscU_OK[bCANALS];

extern  uint                    mpcwEscV_Error[bCANALS],
                                mpcwEscS_Error[bCANALS],
                                mpcwEscU_Error[bCANALS];



extern  bool                    boDsblEscU, boDsblEscV, boDsblEscS;

extern  bool                    boMntEscS;

extern  bool                    boExtendedEscU, boExtendedEscV, boExtendedEscS;

