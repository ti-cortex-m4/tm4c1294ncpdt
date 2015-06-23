/*------------------------------------------------------------------------------
GAPS.H

 Тарифные периоды: Отчет №66 от 17_08_2010
------------------------------------------------------------------------------*/

extern  cache const             chGapsFlag;
extern  file const              flGaps;



void    InitGaps(void);
void    ResetGaps(void);

uchar   GetGapSize(void);
void    SetGapSize(uchar  bSize);

void    GetGapDate(uchar  ibGap);
void    SetGapDate(uchar  ibGap);

void    MakeGaps(void);
