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

void    MakeCRCElsInBuff(uchar  bOffset, uint  wSize);

uchar   MakeCrcSOutBuff(uchar  bOffset, uint  wSize);
uchar   MakeCrcSInBuff(uchar  bOffset, uint  wSize);

uchar   MakeCrcVOutBuff(uchar  bOffset, uint  wSize);
uchar   MakeCrcVInBuff(uchar  bOffset, uint  wSize);

uchar   MakeCrcN31OutBuff(uchar  bOffset, uint  wSize);
uchar   MakeCrcN31InBuff(uchar  bOffset, uint  wSize);
