/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

extern  time const              tiZero;
extern  time                    tiAlt;


uchar   GetDaysInMonthM(uchar  bMonth);
uchar   GetDaysInMonthYM(uchar  bYear, uchar  bMonth);
uint    GetDaysInYearY(uchar  bYear);
uchar   GetWeekdayYMD(uchar  bYear, uchar  bMonth, uchar  bDay);
time   *GetDecretDateYM(uchar  bYear, uchar  bMonth);
uint    GetDayIndexYMD(uchar  bYear, uchar  bMonth, uchar  bDay);
uint    GetDayIndexMD(uchar  bMonth, uchar  bDay);
bool    TrueTimeDate(void);
