/*------------------------------------------------------------------------------
GAPS.H


------------------------------------------------------------------------------*/

extern  cache const             chGapsFlag;
extern  cache const             chGaps;



void    InitGaps(void);
void    ResetGaps(void);

uchar   GetGapSize(void);
void    SetGapSize(uchar  bSize);

void    GetGapDate(uchar  ibGap);
void    SetGapDate(uchar  ibGap);

void    MakeGaps(void);
