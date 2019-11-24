/*------------------------------------------------------------------------------
STATUS35!H


------------------------------------------------------------------------------*/

extern volatile serial         Serial35;

void    SetCurr35Internal(device  de);
device  GetCurr35Internal(void);

void    SetCurr35(device  de);

bool    IsSerial35(void);
