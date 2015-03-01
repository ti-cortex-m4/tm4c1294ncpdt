/*------------------------------------------------------------------------------
CALENDAR.H


------------------------------------------------------------------------------*/

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
