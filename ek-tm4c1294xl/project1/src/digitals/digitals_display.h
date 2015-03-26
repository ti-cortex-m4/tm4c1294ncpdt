/*------------------------------------------------------------------------------
DIGITALS_DISPLAY.H


------------------------------------------------------------------------------*/

void    ShowDigital(uchar  ibCan);
void    ShowCanalNumber(uchar  ibCan);
void    ShowPort(uchar  ibPort);

void    ShowPortDelayHi(uchar  ibPrt);
void    ShowPortDelayLo(uchar  ibPrt);

void    ShowDeltaPos(uchar  ibCan, ulong  dwSecond);
void    ShowDeltaNeg(uchar  ibCan, ulong  dwSecond);
