/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

void    InitPush(uchar  ibPush);
void    InitPushCRC(void);
void    InitPushPtr(void);

void    Push(void  *pbData, uint  wSize);
void    PushChar(uchar  bT);
void    PushInt(uint  wT);
void    PushLong(ulong  dwT);
void    PushReal(real  reT);
void    PushTime(time  *pti);

uchar   SkipChar(void);
void    Skip(uint  wSize);

void    InitPop(uint  i);

void    Pop(void  *pbData, uint  wSize);
uchar   PopChar(void);
