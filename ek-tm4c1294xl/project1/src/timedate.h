/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

extern  time                    tiZero;
extern  time                    tiAlt;


uchar   GetDaysInMonthM(uchar  bMonth);
uchar   GetDaysInMonthYM(uchar  bYear, uchar  bMonth);
uint    GetDaysInYearY(uchar  bYear);
uchar   Weekday(void);
uint    GetDayIndexYMD(uchar  bYear, uchar  bMonth, uchar  bDay);
uint    GetDayIndexMD(uchar  bMonth, uchar  bDay);
bool    TrueTimeDate(void);
void    DecretDate(void);

ulong   DateToSecIndex(void);
void    SecIndexToDate(ulong  dwT);

void    ShowTime(void);
void    ShowDate(void);
void    ShowTimeDate(void);

void    LoadBetaMonth(uchar  ibMonth);
