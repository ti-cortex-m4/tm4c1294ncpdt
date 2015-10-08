/*------------------------------------------------------------------------------
DEVICE_V.H


------------------------------------------------------------------------------*/

extern  uint                    wDividerV;



void    QueryTimeV(void);
time    ReadTimeV(void);

//void    QueryControlS(time  ti);
//
//void    QueryConfigS(void);
//void    ReadConfigS(void);
//
//void    QueryVersionS(void);
//void    ReadVersionS(void);

void    QueryEngAbsV(void);
void    QueryEngMonV(uchar  bMonth, uchar  bYear);
void    QueryEngDayV(uchar  bDay, uchar  bMonth, uchar  bYear);
void    ReadEnergyV(void);

//void    InitHeaderS(void);
//void    QueryHeaderS(void);
//bool    ReadHeaderS(void);
//
//void    ReadCurrentS(void);
