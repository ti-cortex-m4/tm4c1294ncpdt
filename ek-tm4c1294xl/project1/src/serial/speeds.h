/*------------------------------------------------------------------------------
SPEEDS.H


------------------------------------------------------------------------------*/

//void    InitSpeeds(void);

bool    IsMaster(uchar  i);
bool    IsSlave(uchar  i);

//void    SetDelay(uchar  i);
//void    ResetAllSerial(void);
//
//void    ResetSpeeds(void);
//void    ResetSendAT(void);
void    SetSpeeds(uchar  i);

void    SetCorrectLimit(uchar  i);
void    MakeCorrectLimit(void);

void    ShowSpeeds(uchar  i, bool fShow);

bool    StreamPort(uchar  i);
bool    StreamPortDirect(uchar  i);
bool    StreamPortModem(uchar  i);
bool    StreamPortCan(uchar  i, uchar  ibCanal);
bool    StreamPortPhoneCan(uchar  i, uchar  ibPhone, uchar  ibCanal);



