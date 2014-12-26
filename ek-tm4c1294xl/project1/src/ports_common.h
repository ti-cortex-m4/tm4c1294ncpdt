/*------------------------------------------------------------------------------
PORTS_COMMON.H


------------------------------------------------------------------------------*/

uchar   InBuff(uint  i);
void    Answer(uint  wSize, serial  seT);
uint    IndexInBuff(void);

void    MakeCRC16OutBuff(uchar  bOffset, uint  wSize);
void    MakeCRC16InBuff(uchar  bOffset, uint  wSize);
