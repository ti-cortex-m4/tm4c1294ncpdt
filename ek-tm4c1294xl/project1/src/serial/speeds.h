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
