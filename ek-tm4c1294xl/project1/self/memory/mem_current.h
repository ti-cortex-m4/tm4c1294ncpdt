/*------------------------------------------------------------------------------
MEM_CURRENT.H


------------------------------------------------------------------------------*/

extern  ulong                   mpdwBase[bCANALS];

extern  float                   mpreBase[bCANALS];

extern  time                    mptiBase[bCANALS];

extern  bool                    mpboBase[bCANALS];

extern  ulong                   mpdwBaseDig[bCHANNELS];

extern  time                    mptiOffs[bCANALS];

extern  time                    tiOffs;

extern  uint                    mpwTrue[bCANALS],
                                mpwFalse[bCANALS],
                                mpwOverflow[bCANALS],
                                mpwUnderflow[bCANALS],
                                mpwRepeat[bCANALS];



extern  uint                    mpwMore100[bCANALS],
                                mpwMore1000[bCANALS],
                                mpwMore10000[bCANALS];

extern  time                    mptiBaseOK[bCANALS],
                                mptiBaseError[bCANALS];



extern  bool                    fCurrent2Enbl;

extern  bool                    boCurrent2;

extern  uchar                   mpbCurrent2Curr[8],
                                mpbCurrent2Prev[8],
                                mpbCurrent2Buff[8];

extern  uint                    mpwCurrent2Mnt[bCANALS];

extern  uint                    mpwCurrent2Overflow[bCANALS];
