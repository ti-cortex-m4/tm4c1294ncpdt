/*------------------------------------------------------------------------------
MEM_DIGITALS.H


------------------------------------------------------------------------------*/

extern  uint                    wDigitalsMask;

extern  boolean                 mpboEnabledCan[bCANALS];



extern  boolean                 boEnableKeys;

extern  phone                   mpphKeys[bCANALS];



extern  digital                 diPrev, diCurr;



extern  boolean                 mpboChannelsA[bCHANNELS];

extern  ulong                   mpdwChannelsA[bCHANNELS],
                                mpdwChannelsB[bCHANNELS];

extern  real                    mpreChannelsA[bCHANNELS],
                                mpreChannelsB[bCHANNELS];

extern  time                    tiChannelC;
