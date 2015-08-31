/*------------------------------------------------------------------------------
MEM_DEVICE_P.H


------------------------------------------------------------------------------*/

extern  uchar                   mpbPasswordEls[8], mpbRandomEls[16], mpbResultEls[16];

extern  uchar                   mpbEls1[8], mpbEls2[16];

extern  uchar                   mpbBuffEls[128];

extern  uchar                   pbPutEls, pbGetEls, cbSizeEls;

extern  uchar                   bFlagElsCurr, bFlagElsPrev;

extern  uchar                   bCodeElsCurr, bCodeElsPrev;

extern  ulong                   dwStampElsCurr, dwStampElsPrev;

extern  uchar                   bBreakEls, bFirstEls;

extern  uchar                   mpbMappingEls[4];

extern  double                  mpdbChannelsEls[4];

extern  bool                    boTimeChangeP;

extern  ulong                   dwHouIndexP, dwHouIndexP1, dwHouIndexP2;

extern  float                   mpreParamP[3];

extern  uint                    cwSecondLockoutP;
