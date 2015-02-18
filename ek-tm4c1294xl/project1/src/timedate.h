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

ulong   DateToSecIndex(time  ti);
time    SecIndexToDate(ulong  dw);

ulong   DateToMntIndex(time  ti);
time    MntIndexToDate(ulong  dw);

ulong   DateToHouIndex(time  ti);
time    HouIndexToDate(ulong  dw);

ulong   DateToDayIndex(time  ti);
time    DayIndexToDate(ulong  dw);

ulong   DateToMonIndex(time  ti);
time    MonIndexToDate(ulong  dw);

void    ShowTime(time  ti);
void    ShowDate(time  ti);
void    ShowTimeDate(time  ti);

void    LoadBetaMonth(uchar  ibMonth);
