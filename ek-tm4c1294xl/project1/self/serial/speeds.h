/*------------------------------------------------------------------------------
SPEEDS!H


------------------------------------------------------------------------------*/

extern  ulong const             mpdwBauds[bBAUDS];



bool    IsMaster(uchar  ibPrt);
bool    IsSlave(uchar  ibPrt);

void    SetDefaultDelay(uchar  ibPrt);
void    SetSpeed(uchar  ibPrt);

void    InitSpeeds(void);
void    ResetSpeeds(void);
