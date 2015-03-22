/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

void    InitPush(uchar  ibPush);
void    InitPushCRC(void);
void    InitPushPtr(void);
void    InitPushUNI(void);

void    Push(void  *pbData, uint  wSize);
void    PushChar(uchar  bT);
void    PushInt(uint  wT);
void    PushLong(ulong  dwT);
void    PushReal(real  reT);
void    PushTime(time  *pti);
void    PushString(char  *psz);
void    PushIntAsString(uint  wT);
void    PushBuffInt(uint  *pwData, uint  wSize);
void    PushBuffLong(ulong  *pdwData, uint  wSize);

uchar   SkipChar(void);
void    Skip(uint  wSize);

void    InitPop(uint  i);

void    Pop(void  *pbData, uint  wSize);
uchar   PopChar(void);
