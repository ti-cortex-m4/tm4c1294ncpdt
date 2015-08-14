/*------------------------------------------------------------------------------
MEM_PROFILE.H


------------------------------------------------------------------------------*/

extern  bool                    boManualProfile;

extern  uint                    cwHouRead;

extern  uint                    cwHouLength;

extern  uint                    mpcwProfile_OK[bCANALS],
                                mpcwProfile_Error[bCANALS],
                                mpcwDigital_OK[bCANALS],
                                mpcwCalcDig[bCANALS];

extern  bool                    fCurrCtrl;



extern  uint                    iwDigHou;

extern  uint                    cwDigHou;



extern  uint                    wBaseCurr, wOffsCurr,
                                wBaseLast;

extern  ulong                   dwBaseCurr;

extern  uchar                   bCurrHouIndex;



extern  uchar                   ibMinor, ibMinorMax;

extern  uint                    iwMajor;



extern  uchar                   bDeltaOld, bDeltaNew;



extern  uchar                   bOutputC0, bOutputC1, bOutputC2;

extern  uint                    mpcwOutputZ[bCANALS],
                                mpcwOutputC[bCANALS],
                                mpcwOutput0[bCANALS],
                                mpcwOutput1[bCANALS],
                                mpcwOutput2[bCANALS],
                                mpcwOutput3[bCANALS];



extern  time                    tiValueA, tiValueB, tiValueC;

extern  ulong                   dwValueC;



extern  float                    mpreBuffCanHou[4][48];
