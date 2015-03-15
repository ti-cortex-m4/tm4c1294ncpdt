/*------------------------------------------------------------------------------
MEM_DIGITALS.H


------------------------------------------------------------------------------*/

extern  uint                    wDigitalsMask;

extern  boolean                 mpboEnblCan[bCANALS];



extern  boolean                 boEnableKeys;

extern  phone                   mpphKeys[bCANALS];



extern  digital                 diPrev, diCurr;



extern  combo                   coEnergy;

extern  boolean                 mpboChannelsA[bCHANNELS];

extern  ulong                   mpdwChannelsA[bCHANNELS],
                                mpdwChannelsB[bCHANNELS];

extern  real                    mpreChannelsA[bCHANNELS],
                                mpreChannelsB[bCHANNELS];

extern  time                    tiChannelC;
