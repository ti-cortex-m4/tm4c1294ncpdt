/*------------------------------------------------------------------------------
SPEEDS.H


------------------------------------------------------------------------------*/

void    InitSpeeds(void);

bool    IsMaster(uchar  ibPrt);
bool    IsSlave(uchar  ibPrt);

void    SetDelay(uchar  ibPrt);
void    SetSpeeds(uchar  ibPrt);

void    SetCorrectLimit(uchar  ibPrt);
void    MakeCorrectLimit(void);

void    ShowSpeeds(uchar  ibPrt, bool  fShowLocalDisable);

bool    StreamPort(uchar  ibPrt);
bool    StreamPortDirect(uchar  ibPrt);
bool    StreamPortModem(uchar  ibPrt);
bool    StreamPortCan(uchar  ibPrt, uchar  ibCan);
bool    StreamPortPhoneCan(uchar  ibPrt, uchar  ibPhn, uchar  ibCan);
