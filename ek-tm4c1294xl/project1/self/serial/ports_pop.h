/*------------------------------------------------------------------------------
PORTS_POP!H


------------------------------------------------------------------------------*/

uint    GetPopSize(void);

uchar   PopChar0Bcc(void);
uchar   PopChar1Bcc(void);
uchar   PopChar2Bcc(void);

uchar   SkipChar(void);
void    Skip(uint  wSize);
void    SkipBack(int  wSize);

void    InitPop(uint  i);

void    Pop(void  *pbData, uint  wSize);
uchar   PopChar(void);
uint    PopIntBig(void);
uint    PopIntLtl(void);
ulong   PopLongBig(void);
ulong   PopLongLtl(void);
float   PopFloat(void);
double  PopDouble(void);
time    PopTime(void);
