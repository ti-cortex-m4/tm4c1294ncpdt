/*------------------------------------------------------------------------------
SPEEDS.H


------------------------------------------------------------------------------*/

//void    InitSpeeds(void);

bool    IsMaster(uchar  ibPrt);
bool    IsSlave(uchar  ibPrt);

void    SetDelay(uchar  i);
//void    ResetAllSerial(void);
//
//void    ResetSpeeds(void);
void    SetSpeeds(uchar  i);

void    SetCorrectLimit(uchar  i);
void    MakeCorrectLimit(void);

void    ShowSpeeds(uchar  i, bool fShow);

bool    StreamPort(uchar  ibPrt);
bool    StreamPortDirect(uchar  ibPrt);
bool    StreamPortModem(uchar  ibPrt);
bool    StreamPortCan(uchar  ibPrt, uchar  ibCan);
bool    StreamPortPhoneCan(uchar  ibPrt, uchar  ibPhn, uchar  ibCan);
