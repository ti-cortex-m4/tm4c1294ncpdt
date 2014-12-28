/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

#include        "main.h"



extern  time                    tiAlt;



bool    TrueTimeDate(void);
uchar   Weekday(void);

uchar   DaysInMonth(void);
uchar   DaysInMonthSpec(uchar  bYear, uchar  bMonth);
uint    DaysInYearSpec(uchar  bYear);

ulong   DateToSecIndex(void);
void    SecIndexToDate(ulong  dwT);

void    ShowTime(void);
void    ShowDate(void);
void    ShowTimeDate(void);
