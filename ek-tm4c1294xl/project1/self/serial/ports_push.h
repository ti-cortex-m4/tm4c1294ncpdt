/*------------------------------------------------------------------------------
PORTS_STACK!H


------------------------------------------------------------------------------*/

void    InitPush(uint  iwPush);
void    InitPushCRC(void);
void    InitPushPtr(void);
void    InitPushUni(void);
void    InitPushPck(void);

void    Push(void  *pbData, uint  wSize);
uchar   PushChar(uchar  b);
uchar   PushBool(bool  f);
uchar   PushIntBig(uint  w);
uchar   PushIntLtl(uint  w);
uint    PushIntBigArray(uint  *mpw, uint  wCount);
uchar   PushLongBig(ulong  dw);
uchar   PushLongLtl(ulong  dw);
uint    PushLongBigArray(ulong  *mpdw, uint  wCount);
uchar   PushFloat(float  fl);
uchar   PushDouble(double  db);
uchar   PushFloatOrDouble(double  db, bool  fDouble);
uchar   GetFloatOrDoubleSize(bool  fDouble);
uchar   PushTime(time  ti);
void    PushString(char  *psz);
void    PushLongAsString(ulong  dw);
void    PushBuffInt(uint  *pwData, uint  wSize);
void    PushBuffLong(ulong  *pdwData, uint  wSize);
void    PushCharHex2Txt(uchar  bT);
void    PushCharDec2Txt(uchar  bT);

void    PushChar1Bcc(uchar  bT);
void    PushChar2Bcc(uchar  bT);
uchar   PushNumberBcc(ulong  dwT);
