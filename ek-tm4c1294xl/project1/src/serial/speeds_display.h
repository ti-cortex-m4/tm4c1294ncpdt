/*------------------------------------------------------------------------------
SPEEDS_DISPLAY.H


------------------------------------------------------------------------------*/

void    ShowSpeeds(uchar  ibPrt, bool  fShowLocalDisable);

bool    StreamPort(uchar  ibPrt);
bool    StreamPortDirect(uchar  ibPrt);
bool    StreamPortModem(uchar  ibPrt);
bool    StreamPortCan(uchar  ibPrt, uchar  ibCan);
bool    StreamPortPhoneCan(uchar  ibPrt, uchar  ibPhn, uchar  ibCan);
