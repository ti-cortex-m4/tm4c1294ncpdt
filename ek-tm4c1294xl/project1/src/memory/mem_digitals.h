/*------------------------------------------------------------------------------
MEM_DIGITALS.H


------------------------------------------------------------------------------*/

extern  uint                    wDigitalsMask;

extern  boolean                 mpboEnblCan[bCANALS];



extern  boolean                 boEnblKeys;

extern  phone                   mpphKeys[bCANALS];

extern  ulong                   mpdwAddress1[bCANALS],
                                mpdwAddress2[bCANALS];



extern  digital                 diPrev, diCurr, diNext, diLast;



extern  combo                   coEnergy;

extern  boolean                 mpboChannelsA[bCHANNELS];

extern  ulong                   mpdwChannelsA[bCHANNELS],
                                mpdwChannelsB[bCHANNELS];

extern  real                    mpreChannelsA[bCHANNELS],
                                mpreChannelsB[bCHANNELS];

extern  time                    tiChannelC;



extern  boolean                 boEnblCurrent, boEnblProfile;

extern  uchar                   bTimeoutCurrent, bTimeoutProfile;

extern  boolean                 boSeparateCan;

extern  boolean                 boShowMessages;

extern  boolean                 boHideMessages;



extern  uchar                   mpboReadyCan[bCANALS];


extern  uint                    mpcwFailure2[bCANALS];
