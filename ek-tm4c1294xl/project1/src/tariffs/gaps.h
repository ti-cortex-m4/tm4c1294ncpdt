/*------------------------------------------------------------------------------
GAPS.H


------------------------------------------------------------------------------*/

uchar   GetGapSize(void);
void    SetGapSize(uchar  bSize);

void    GetGapDate(uchar  ibGap);
void    SetGapDate(uchar  ibGap);

uint    GetDayIndex_Alt(void);
uint    GetDayIndex_Gap(void);
uchar   DaysInMonth_Gap(void);

void    DefaultGaps(void);
void    ResetGaps(void);

void    MakeGaps(void);

void    ShowGapName(uchar  ibMode);
void    ShowGap(uchar  ibGap);

void    OutGaps1(void); 
void    OutGaps2(void); 
