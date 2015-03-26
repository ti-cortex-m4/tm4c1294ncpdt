/*------------------------------------------------------------------------------
MEM_PROFILE.H


------------------------------------------------------------------------------*/

extern  boolean                 boManualProfile;

extern  uint                    cwHouRead;

extern  uint                    cwHouLength;

extern  uint                    mpcwProfile_OK[bCANALS],
                                mpcwProfile_Error[bCANALS],
                                mpcwDigital_OK[bCANALS],
                                mpcwCalcDig[bCANALS];

extern  bool                    fCurrCtrl;



extern  uint                    wBaseCurr, wOffsCurr,
                                wBaseLast;

extern  ulong                   dwBaseCurr;



extern  uchar                   ibMinor, ibMinorMax;

extern  uint                    iwMajor;
