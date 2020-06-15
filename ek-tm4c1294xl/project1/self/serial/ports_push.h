/*------------------------------------------------------------------------------
PORTS_STACK!H


------------------------------------------------------------------------------*/

uint    GetPushSize(void);

void    InitPush(uint  iwPush);
uint    GetPush(void);
void    InitPushCRC(void);
void    InitPushPtr(void);
void    InitPushUni(void);
void    InitPushPck(void);

uint    Push(void  *pbData, uint  wSize);
uchar   PushChar(uchar  b);
uchar   PushBool(bool  f);
uint    PushBoolArray(bool  *mpf, uchar  bCount);
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
uint    PushString(char  *psz);
void    PushLongAsString(ulong  dw);
void    PushBuffInt(uint  *pwData, uint  wSize);
void    PushBuffLong(ulong  *pdwData, uint  wSize);
void    PushCharHex2Txt(uchar  bT);
uchar   PushCharDec2Txt(uchar  bT);
uchar   PushFloat3(float  fl);

void    PushChar1Bcc(uchar  bT);
void    PushChar2Bcc(uchar  bT);
uchar   PushNumberBcc(ulong  dwT);
void    PushStringBcc(char  *psz);

