/*------------------------------------------------------------------------------
PORTS2!H


------------------------------------------------------------------------------*/

void    SetOutBuff(uint  i, uchar  bT);

void    SetInBuff(uint  i, uchar  bT);
void    SetIndexInBuff(uint  wT);
void    SetCountInBuff(uint  wT);
void    InputMode(void);

uchar*  OutBuffPtr(uint  i);
uchar*  InBuffPtr(uint  i);
