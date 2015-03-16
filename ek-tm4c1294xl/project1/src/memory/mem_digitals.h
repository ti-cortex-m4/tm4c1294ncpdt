/*------------------------------------------------------------------------------
MEM_DIGITALS.H


------------------------------------------------------------------------------*/

extern  uint                    wDigitalsMask;

extern  boolean                 mpboEnblCan[bCANALS];



extern  boolean                 boEnableKeys;

extern  phone                   mpphKeys[bCANALS];



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

extern  boolean                 boHideMessages;



extern  uchar                   mpboReadyCan[bCANALS];



extern  uint                    mpcwBaud[bPORTS],
                                mpcwCommon[bPORTS],
                                mpcwCustom[bPORTS],
                                mpcwConnect[bPORTS],
                                mpcwEscape[bPORTS],
                                mpcwHookOff[bPORTS],
                                mpcwDTROff[bPORTS];
