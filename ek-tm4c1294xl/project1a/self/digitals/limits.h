/*------------------------------------------------------------------------------
LIMITS!H


------------------------------------------------------------------------------*/

extern  cache const             chUseBounds;

extern  cache const             chStartRelCan;
extern  cache const             chStartAbs16Can;
extern  cache const             chStartAbs32Can;
extern  cache const             chStartCan;
extern  cache const             chStopCan;



void    InitLimits(void);
void    ResetLimits(void);

bool    UseBounds(void);
void    NewBoundsRel(uint  wRel);
void    NewBoundsAbs16(uint  wAbs);
void    NewBoundsAbs32(ulong  dwAbs);

void    NewLimits(void);
void    MakeLimits(void);

void    ResetLimitsAux(uchar  ibDig);
void    NextHouLimitsAux(void);
