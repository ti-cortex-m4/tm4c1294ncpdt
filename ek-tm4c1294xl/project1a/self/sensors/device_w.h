/*------------------------------------------------------------------------------
DEVICE_W.H


------------------------------------------------------------------------------*/

#define MAX_LINE_W      4



extern  uchar                   ibLineW;

extern  time                    tiProfileW;

extern  slong                   dwCorrectW;

extern  uint                    wProfileW;



double  PopDoubleW(void);

uchar   PushAddressW_DirectRead(void);

void    QueryCloseW(void);
void    QueryOpenW(void);

void    QueryTypeW(void);
void    ReadTypeW(void);

void    QueryTimeW(void);
time    ReadTimeW(void);

void    QueryControlW(time  ti);
void    QueryGetCorrectW(void);
uint    ReadGetCorrectW(void);
void    QuerySetCorrectW(sint  wSecond);

void    QueryOptionW(void);
void    QueryPasswordW(void);

void    QueryTransW(uchar  ibTrans);

void    QueryEngAbsW_Current(uchar  ibLine);
void    QueryEngAbsW(uchar  ibLine);
void    QueryEngMonW(uchar  ibLine, uchar  bTime);
void    QueryEngDayW(uchar  ibLine, uchar  bTime);
void    QueryEngMonTrfW(uchar  ibLine, uchar  bTime);

void    ReadEngW(uchar  ibLine);
void    ReadEngTrfW(uchar  ibLine, uchar  ibTrf);

void    InitProfileW(void);
void    QueryProfileW(void);
bool    ReadProfileW(void);

void    ReadCurrentW(void);
