/*------------------------------------------------------------------------------
PORTS_COMMON!H


------------------------------------------------------------------------------*/

void    Answer(uint  wSize, serial  seT);

uchar   InBuff(uint  i);
uint    InBuffIntBig(uint  i);
uint    InBuffIntLtl(uint  i);

uint    CountInBuff(void);
uint    IndexInBuff(void);

uchar   OutBuff(uint  i);

void    MakeCRC16OutBuff(uchar  bOffset, uint  wSize);
void    MakeCRC16InBuff(uchar  bOffset, uint  wSize);

void    MakeCrcSOutBuff(uchar  bOffset, uint  wSize);
void    MakeCrcSInBuff(uchar  bOffset, uint  wSize);

void    MakeCRCElsInBuff(uchar  bOffset, uint  wSize);

uchar   MakeCrcVOutBuff(uchar  bOffset, uint  wSize);
uchar   MakeCrcVInBuff(uchar  bOffset, uint  wSize);

