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

void    MakeGaps(void);
