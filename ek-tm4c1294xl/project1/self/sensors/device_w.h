/*------------------------------------------------------------------------------
DEVICE_W.H


------------------------------------------------------------------------------*/

//extern  uint                    wDividerV;
//
//extern  ulong                   dwTimeV;



void    QueryCloseW(void);

//void    PushAddressV(uchar  bCode);

void    QueryTimeW(void);
time    ReadTimeW(void);

//void    QueryControlV(time  ti);
//
//void    QueryVersionV(void);
//bool    ReadVersionV(void);

void    QueryEngAbsW(uchar  ibLine);
void    QueryEngMonW(uchar  ibLine, uchar  bTime);
void    QueryEngDayW(uchar  ibLine, uchar  bTime);

void    ReadEngAbsW(uchar  ibLine);
//void    ReadEngMonV(void);
//void    ReadEngDayV(void);
//
//void    InitHeaderV(void);
//void    QueryHeaderV(void);
//bool    ReadHeaderV(void);
//
//void    ReadCurrentV(void);
