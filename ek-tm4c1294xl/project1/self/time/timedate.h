/*------------------------------------------------------------------------------
TIMEDATE!H


------------------------------------------------------------------------------*/

extern  time const              tiZero;



uchar   GetDaysInMonthM(uchar  bMonth);
uchar   GetDaysInMonthYM(uchar  bYear, uchar  bMonth);
uint    GetDaysInYearY(uchar  bYear);
uchar   GetWeekdayYMD(uchar  bYear, uchar  bMonth, uchar  bDay);
time   *GetDecretDateYM(uchar  bYear, uchar  bMonth);
uint    GetDayIndexYMD(uchar  bYear, uchar  bMonth, uchar  bDay);
uint    GetDayIndexMD(uchar  bMonth, uchar  bDay);

bool    ValidTimeDate(time  ti);

ulong   GetSecondIndex(time  ti);

bool    DifferentDay(time  ti1, time  ti2);
bool    DifferentDateTime(time  ti1, time  ti2);
