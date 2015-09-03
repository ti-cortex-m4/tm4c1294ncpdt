/*------------------------------------------------------------------------------
MEM_EXTENDED_3,H


------------------------------------------------------------------------------*/

extern  bool                    boExt3Flag;

extern  bool                    mpboEventFirst[bCANALS];

extern  bool                    mpboEventA[32],
                                mpboEventB[32];

extern  time                    mptiEventAB1[10],
                                mptiEventAB2[10];

extern  ulong                   mpdwEventDevice[bCANALS],
                                mpdwEventPhase1[bCANALS],
                                mpdwEventPhase2[bCANALS],
                                mpdwEventPhase3[bCANALS];

extern  ulong                   dwEventIndexCurr, dwEventIndexPrev;

extern  uchar                   bEventCode;
