/*------------------------------------------------------------------------------
DEVICE_V.H


------------------------------------------------------------------------------*/

extern  uint                    wDividerV;

extern  ulong                   dwTimeV;



void    PushAddressV(uchar  bCode);

void    QueryTimeV(void);
time    ReadTimeV(void);

void    QueryControlV(time  ti);

void    QueryVersionV(void);
bool    ReadVersionV(void);

void    QueryEngAbsV(void);
void    QueryEngMonV(uchar  bMonth, uchar  bYear);
void    QueryEngDayV(uchar  bDay, uchar  bMonth, uchar  bYear);

void    ReadEngAbsV(void);
void    ReadEngMonV(void);
void    ReadEngDayV(void);

void    InitHeaderV(void);
void    QueryHeaderV(void);
bool    ReadHeaderV(void);

void    ReadCurrentV(void);
