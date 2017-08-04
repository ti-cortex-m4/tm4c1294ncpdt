/*------------------------------------------------------------------------------
MEM_EXTENDED_3,H


------------------------------------------------------------------------------*/

extern  bool                    fExt3Flag;

extern  bool                    mpfEventStart[bCANALS];

extern  bool                    mpfEventFlagA[32],
                                mpfEventFlagB[32];

extern  time                    mptiEventAB1[10],
                                mptiEventAB2[10];

extern  ulong                   mpdwEventDevice[bCANALS],
                                mpdwEventPhase1[bCANALS],
                                mpdwEventPhase2[bCANALS],
                                mpdwEventPhase3[bCANALS];

extern  uchar                   bEventCode;
