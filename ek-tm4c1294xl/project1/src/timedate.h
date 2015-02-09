/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

extern  time                    tiZero;
extern  time                    tiAlt;


uchar   GetDaysInMonthM(uchar  bMonth);
uchar   GetDaysInMonthYM(uchar  bYear, uchar  bMonth);
uint    GetDaysInYearY(uchar  bYear);
uchar   GetWeekdayYMD(uchar  bYear, uchar  bMonth, uchar  bDay);
time   *GetDecretDateYM(uchar  bYear, uchar  bMonth);
uint    GetDayIndexYMD(uchar  bYear, uchar  bMonth, uchar  bDay);
uint    GetDayIndexMD(uchar  bMonth, uchar  bDay);
bool    TrueTimeDate(void);

ulong   DateToSecIndex(void);
void    SecIndexToDate(ulong  dwT);

void    ShowTime(void);
void    ShowDate(void);
void    ShowTimeDate(void);

void    LoadBetaMonth(uchar  ibMonth);
