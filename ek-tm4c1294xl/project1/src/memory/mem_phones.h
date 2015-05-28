/*------------------------------------------------------------------------------
MEM_PHONES.H


------------------------------------------------------------------------------*/

extern  phone                   mpphPhones[bCANALS];

extern  uchar                   bMaxConnect;

extern  bool                 boCustomModem;

extern  uint                    mpcwBaud[bPORTS],
                                mpcwCommon[bPORTS],
                                mpcwCustom[bPORTS],
                                mpcwConnect[bPORTS],
                                mpcwEscape[bPORTS],
                                mpcwHookOff[bPORTS],
                                mpcwDTROff[bPORTS];
