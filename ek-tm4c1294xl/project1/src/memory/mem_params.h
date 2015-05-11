/*------------------------------------------------------------------------------
MEM_PARAMS.H


------------------------------------------------------------------------------*/

extern  boolean                 boParamsFlag;

extern  boolean                 boMntParams;

extern  digital                 mpdiParam[wPARAMS];

extern  real                    mpreParamsDiv[wPARAMS];

extern  boolean                 mpboEnblParams[wPARAMS];

extern  real                    mpreParBuff[2][wPARAMS];

extern  time                    mptiParBuff[wPARAMS];

extern  uchar                   ibSoftTim;

extern  uint                    iwHardTim;

extern  uint                    cwParamTim;

extern  boolean                 boFixParamsBugs;

extern  boolean                 boUseParamsDiv;
