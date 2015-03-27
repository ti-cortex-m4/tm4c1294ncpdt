/*------------------------------------------------------------------------------
LIMITS.H


------------------------------------------------------------------------------*/

extern  file const              flUseBounds;

extern  file const              flStartRelCan;
extern  file const              flStartAbs16Can;
extern  file const              flStartAbs32Can;
extern  file const              flStartCan;
extern  file const              flStopCan;



void    InitLimits(void);
void    ResetLimits(void);

bool    UseBounds(void);
void    NewBoundsRel(uint  i);
void    NewBoundsAbs(uint  i);
void    NewBoundsAbs2(ulong  dw);

void    NewLimits(void);
void    MakeLimits(void);

void    ResetLimitsAux(uchar  ibDig);
void    ResetLimitsAux_All(void);
void    NextHouLimitsAux(void);
