/*------------------------------------------------------------------------------
_AUTOMATIC1!H


------------------------------------------------------------------------------*/

extern  double                  dbKtrans, dbKpulse;



void    SetAllFactors(double  dbPulse, double  dbTrans);
void    SetupFactors(factors  fc);

bool    ReadKoeffDeviceA(void);
bool    ReadKoeffDeviceB(uchar  ibCan);
bool    ReadKoeffDeviceB_Special(uchar  ibCan);
bool    ReadKoeffDeviceC(uchar  ibCan);
bool    ReadKoeffDeviceP(void);

bool    OpenDeviceP(void);

bool    AutomaticA(void);
bool    AutomaticB(uchar  ibCan);
bool    AutomaticC(uchar  ibCan);
bool    AutomaticJ(uchar  ibCan);
bool    AutomaticK(void);
bool    AutomaticP(void);
bool    AutomaticS(void);
bool    AutomaticV(void);
