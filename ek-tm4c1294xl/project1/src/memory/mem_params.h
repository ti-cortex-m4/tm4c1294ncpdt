/*------------------------------------------------------------------------------
MEM_PARAMS.H


------------------------------------------------------------------------------*/

extern  boolean                 boEnblAllParams;

extern  boolean                 boMntParams;

extern  boolean                 boFixParamsBugs;

extern  digital                 mpdiParam[wPARAMS];

extern  real                    mpreParamDiv[wPARAMS];

extern  boolean                 mpboEnblPar[wPARAMS];

extern  real                    mpreParBuff[2][wPARAMS];

extern  time                    mptiParBuff[wPARAMS];

extern  uchar                   ibSoftTim;

extern  uint                    iwHardTim;

extern  uint                    cwParamTim;
