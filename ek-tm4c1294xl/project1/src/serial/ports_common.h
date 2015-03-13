/*------------------------------------------------------------------------------
PORTS_COMMON.H


------------------------------------------------------------------------------*/

void    Answer(uint  wSize, serial  seT);

uchar   InBuff(uint  i);
uint    CountInBuff(void);
uint    IndexInBuff(void);

void    MakeCRC16OutBuff(uchar  bOffset, uint  wSize);
void    MakeCRC16InBuff(uchar  bOffset, uint  wSize);
