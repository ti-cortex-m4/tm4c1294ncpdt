/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

void    InitPush(void);
void    InitPushCRC(void);
void    InitPushPtr(void);

void    Push(void  *pbData, uint  wSize);
void    PushChar(uchar  bT);
void    PushInt(uint  wT);
uchar   SkipChar(void);
void    Skip(uint  wSize);

void    InitPop(uint  i);

void    Pop(void  *pbData, uint  wSize);
uchar   PopChar(void);
