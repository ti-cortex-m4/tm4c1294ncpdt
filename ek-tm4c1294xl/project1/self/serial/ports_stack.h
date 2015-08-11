/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

void    InitPush(uint  iwPush);
void    InitPushCRC(void);
void    InitPushPtr(void);
void    InitPushUni(void);
void    InitPushPck(void);

void    Push(void  *pbData, uint  wSize);
uchar   PushChar(uchar  b);
uchar   PushBool(bool  f);
uchar   PushInt(uint  w);
uchar   PushLong(ulong  dw);
uchar   PushFloat(float  fl);
uchar   PushDouble(double  db);
uchar   PushFloatOrDouble(double  db, bool  fDouble);
uchar   PushTime(time  ti);
void    PushString(char  *psz);
void    PushLongAsString(ulong  dw);
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
double  PopDouble(void);
