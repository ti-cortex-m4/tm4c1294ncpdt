/*------------------------------------------------------------------------------
PORTS_POP!H


------------------------------------------------------------------------------*/

uchar   PopChar0Bcc(void);
uchar   PopChar1Bcc(void);
uchar   PopChar2Bcc(void);

uchar   SkipChar(void);
void    Skip(uint  wSize);

void    InitPop(uint  i);

void    Pop(void  *pbData, uint  wSize);
uchar   PopChar(void);
uint    PopInt(void);
ulong   PopLong(void);
float   PopFloat(void);
double  PopDouble(void);
time    PopTime(void);
