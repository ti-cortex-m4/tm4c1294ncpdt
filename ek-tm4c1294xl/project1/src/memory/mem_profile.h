/*------------------------------------------------------------------------------
MEM_PROFILE.H


------------------------------------------------------------------------------*/

extern  boolean                 boManualProfile;



extern  uint                    mpcwEscV_OK[bCANALS], mpcwEscV_Error[bCANALS],
                                mpcwEscS_OK[bCANALS], mpcwEscS_Error[bCANALS],
                                mpcwEscU_OK[bCANALS], mpcwEscU_Error[bCANALS];

extern  uint                    mpcwProfile_OK[bCANALS],
                                mpcwProfile_Error[bCANALS];

extern  boolean                 mpboDefEscV[bCANALS],
                                mpboDefEscS[bCANALS],
                                mpboDefEscU[bCANALS];
