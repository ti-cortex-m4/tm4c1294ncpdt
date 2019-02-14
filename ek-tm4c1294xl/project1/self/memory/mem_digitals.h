/*------------------------------------------------------------------------------
MEM_DIGITALS!H


------------------------------------------------------------------------------*/

extern  volatile uint           wDigitalsMask;

extern  bool                    mpboEnblCan[bCANALS];



extern  bool                    boEnblKeys;

extern  line                    mpphKeys[bCANALS];

extern  ulong                   mpdwAddress1[bCANALS],
                                mpdwAddress2[bCANALS];



extern  digital                 diPrev, diCurr, diNext, diLast;



extern  combo32                 coEnergy;

extern  bool                    mpboChannelsA[bCHANNELS];

extern  ulong                   mpdwChannelsA[bCHANNELS],
                                mpdwChannelsB[bCHANNELS];

extern  double                  mpdbChannelsC[bCHANNELS];

extern  time                    tiChannelC;



extern  bool                    boEnblCurrent, boEnblProfile;

extern  uchar                   bTimeoutCurrent, bTimeoutProfile;

extern  bool                    boSeparateCan;

extern  bool                    boShowMessages;

extern  bool                    boHideMessages;

extern  bool                    boControlTime;

extern  bool                    boManageTime;



extern  uchar                   mpboReadyCan[bCANALS];


extern  uint                    mpcwFailure2[bCANALS];



extern  uchar                   bKeysLevelB;

extern  bool                    boShortProfileC;

extern  bool                    boControlQ;

extern  bool                    boControlK;

extern  bool                    boPlcUFlag;

extern  uchar                   bPlcUSize;

extern  uint                    wPlcUShutdown;

extern  bool                    boControlW;



extern  bool                    fDsblAnswer;

extern  bool                    fEnblAnswerCurr;

extern  ulong                   cdwAnswerDisabled, cdwAnswerEnabled;

extern  time                    tiAnswerDisabled, tiAnswerEnabled;



extern  uchar                   bTimeZone34;

extern  uint64_t                mpddwChannels34[8+2];

extern  double                  mpdbEngFracDigCan8[bCANALS][8];
