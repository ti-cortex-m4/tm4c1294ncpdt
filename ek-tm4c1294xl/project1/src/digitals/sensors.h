/*------------------------------------------------------------------------------
SENSORS.H


------------------------------------------------------------------------------*/

ulong   GetMajorDelay(uchar  ibPort);
ulong   GetMinorDelay(uchar  ibPort);

bool    IsPulseCanal(uchar  ibCan);

void    InitWaitAnswer(void);
void    ShowWaitAnswer(bool  fShow);
bool    GetWaitAnswer(void);
