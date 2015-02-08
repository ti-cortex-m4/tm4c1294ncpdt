/*------------------------------------------------------------------------------
GAPS.H


------------------------------------------------------------------------------*/

extern  file const              flGapsFlag;
extern  file const              flGaps;



void    InitGaps(void);
void    ResetGaps(void);

uchar   GetGapSize(void);
void    SetGapSize(uchar  bSize);

void    GetGapDate(uchar  ibGap);
void    SetGapDate(uchar  ibGap);

uint    GetDayIndex_Alt(void);
uint    GetDayIndex_Gap(void);
uchar   DaysInMonth_Gap(void);

void    MakeGaps(void);
