/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

void    InitPush(uchar  ibPush);
void    InitPushCRC(void);
void    InitPushPtr(void);
void    InitPushUni(void);
void    InitPushPck(void);

void    Push(void  *pbData, uint  wSize);
void    PushChar(uchar  bT);
void    PushBool(bool  bo);
void    PushInt(uint  wT);
void    PushLong(ulong  dwT);
void    PushFloat(float  fl);
void    PushDouble(double  db);
uint    PushFloatOrDouble(double  db, bool  fDouble);
void    PushFloatBCD(float  fl);
void    PushTime(time  ti);
void    PushString(char  *psz);
void    PushIntAsString(uint  wT);
void    PushBuffInt(uint  *pwData, uint  wSize);
void    PushBuffLong(ulong  *pdwData, uint  wSize);
void    PushCharHex2Txt(uchar  bT);
void    PushCharDec2Txt(uchar  bT);

uchar   SkipChar(void);
void    Skip(uint  wSize);

void    InitPop(uint  i);

void    Pop(void  *pbData, uint  wSize);
uchar   PopChar(void);
ulong   PopLong(void);
float   PopFloat(void);
