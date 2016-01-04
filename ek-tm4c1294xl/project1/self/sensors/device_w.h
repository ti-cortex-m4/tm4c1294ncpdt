/*------------------------------------------------------------------------------
DEVICE_W.H


------------------------------------------------------------------------------*/

//extern  uint                    wDividerV;
//
//extern  ulong                   dwTimeV;

double  PopDoubleW(void);

void    QueryCloseW(void);

//void    PushAddressV(uchar  bCode);

void    QueryTimeW(void);
time    ReadTimeW(void);

//void    QueryControlV(time  ti);
//
//void    QueryVersionV(void);
//bool    ReadVersionV(void);

void    QueryKtransW(uchar  ibKtrans);

void    QueryEngAbsW(uchar  ibLine);
void    QueryEngMonW(uchar  ibLine, uchar  bTime);
void    QueryEngDayW(uchar  ibLine, uchar  bTime);

void    ReadEngW(uchar  ibLine);

//void    InitHeaderV(void);
//void    QueryHeaderV(void);
//bool    ReadHeaderV(void);
//
//void    ReadCurrentV(void);
