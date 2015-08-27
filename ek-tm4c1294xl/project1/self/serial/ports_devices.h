/*------------------------------------------------------------------------------
PORTS_DEVICES.H


------------------------------------------------------------------------------*/

void    Query(uint  cwIn, uchar  cbOut, bool  fMinor);

void    QueryIO(uint  cwIn, uchar  cbOut);
serial  Input(void);

void    RevQueryIO(uint  cwIn, uchar  cbOut);
bool    RevLinkErrors(void);
serial  RevInput(void);

void    PckQueryIO(uint  cwIn, uchar  cbOut);

void    BccQueryIO1(uint  cwIn, uchar  cbOut, uchar  cbMaxHeader);
void    BccQueryIO2(uint  cwIn, uchar  cbOut, uchar  cbMaxHeader);
bool    MakeBccInBuff(void);
serial  BccInput(void);

#ifndef SKIP_P
void    ElsQueryIO(uint  cbIn, uchar  cbOut);
bool    MakeElsInBuff0(void);
bool    MakeElsInBuff1(void);
bool    MakeElsInBuff2(void);
serial  ElsInput(uchar  bMode);
serial  ElsInputRD(void);
#endif

void    ChecksumError(void);
void    TestResult(uchar  bT);
