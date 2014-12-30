/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

#include        "main.h"



extern  time                    tiZero;
extern  time                    tiAlt;



uchar   DaysInMonth(void);
uchar   DaysInMonthSpec(uchar  bYear, uchar  bMonth);
uint    DaysInYearSpec(uchar  bYear);

uchar   Weekday(void);
bool    TrueTimeDate(void);
void    DecretDate(void);

ulong   DateToSecIndex(void);
void    SecIndexToDate(ulong  dwT);

void    ShowTime(void);
void    ShowDate(void);
void    ShowTimeDate(void);
