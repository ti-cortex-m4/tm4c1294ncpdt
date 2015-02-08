/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

extern  time                    tiZero;
extern  time                    tiAlt;


uchar   GetDaysInMonth(uchar  bMonth);
uchar   GetDaysInYearMonth(uchar  bYear, uchar  bMonth);
uint    GetDaysInYear(uchar  bYear);
uchar   Weekday(void);
uint    GetDayIndexYearMonthDay(uchar  bYear, uchar  bMonth, uchar  bDay);
uint    GetDayIndexMonthDay(uchar  bMonth, uchar  bDay);
bool    TrueTimeDate(void);
void    DecretDate(void);

ulong   DateToSecIndex(void);
void    SecIndexToDate(ulong  dwT);

void    ShowTime(void);
void    ShowDate(void);
void    ShowTimeDate(void);

void    LoadBetaMonth(uchar  ibMonth);
