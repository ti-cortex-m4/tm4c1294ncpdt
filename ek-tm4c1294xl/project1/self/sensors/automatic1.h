/*------------------------------------------------------------------------------
_AUTOMATIC1!H


------------------------------------------------------------------------------*/

extern  double                  dbKtrans, dbKpulse;



void    SetAllFactors(double  dbPulse, double  dbTrans);
void    SetupFactors(factors  fc);

bool    ReadKoeffDeviceA(void);
bool    ReadKoeffDeviceB(void);
bool    ReadKoeffDeviceB_Special(void);
bool    ReadKoeffDeviceC(void);
bool    ReadKoeffDeviceP(void);

bool    OpenDeviceP(void);

bool    AutomaticA(void);
bool    AutomaticB(void);
bool    AutomaticC(void);
bool    AutomaticJ(void);
bool    AutomaticK(void);
bool    AutomaticP(void);
bool    AutomaticS(void);
bool    AutomaticV(void);
