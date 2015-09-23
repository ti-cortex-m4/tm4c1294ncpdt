/*------------------------------------------------------------------------------
PORTS_COMMON!H


------------------------------------------------------------------------------*/

void    Answer(uint  wSize, serial  seT);

uchar   InBuff(uint  i);
uint    CountInBuff(void);
uint    IndexInBuff(void);

void    MakeCRC16OutBuff(uchar  bOffset, uint  wSize);
void    MakeCRC16InBuff(uchar  bOffset, uint  wSize);

void    MakeCrcSOutBuff(uchar  bOffset, uint  wSize);
void    MakeCrcSInBuff(uchar  bOffset, uint  wSize);

void    MakeCRCElsInBuff(uchar  bOffset, uint  wSize);
