/*------------------------------------------------------------------------------
_AUTOMATIC1.H
              

------------------------------------------------------------------------------*/

extern  real                    reKtrans, reKpulse;



bool    ReadKoeffDeviceA(void);
bool    ReadKoeffDeviceB(void);
bool    ReadKoeffDeviceB_Special(void);
bool    ReadKoeffDeviceC(void);

bool    AutomaticA(void);
bool    AutomaticB(void);
bool    AutomaticC(void);
bool    AutomaticJ(void);
