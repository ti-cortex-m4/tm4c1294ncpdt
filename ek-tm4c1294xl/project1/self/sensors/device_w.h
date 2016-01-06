/*------------------------------------------------------------------------------
DEVICE_W.H


------------------------------------------------------------------------------*/

#define MAX_LINE_W      4

extern  uchar                   ibLineW;



double  PopDoubleW(void);

void    QueryCloseW(void);
void    QueryOpenW(void);

void    QueryTypeW(void);
void    ReadTypeW(void);

void    QueryTimeW(void);
time    ReadTimeW(void);

void    QueryOptionW(void);

//void    QueryControlV(time  ti);
//
//void    QueryVersionV(void);
//bool    ReadVersionV(void);

void    QueryKtransW(uchar  ibKtrans);

void    QueryEngSpecW(uchar  ibLine);
void    QueryEngAbsW(uchar  ibLine);
void    QueryEngMonW(uchar  ibLine, uchar  bTime);
void    QueryEngDayW(uchar  ibLine, uchar  bTime);

void    ReadEngW(uchar  ibLine);

//void    InitHeaderV(void);
//void    QueryHeaderV(void);
//bool    ReadHeaderV(void);

void    ReadCurrentW(void);
