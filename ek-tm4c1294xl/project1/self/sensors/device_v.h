/*------------------------------------------------------------------------------
DEVICE_V.H


------------------------------------------------------------------------------*/

extern  uint                    wDividerV;

extern  ulong                   dwValueV;



void    QueryTimeV(void);
time    ReadTimeV(void);

//void    QueryControlS(time  ti);
//
//void    QueryConfigS(void);
//void    ReadConfigS(void);

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
