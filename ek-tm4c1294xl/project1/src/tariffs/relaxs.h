/*------------------------------------------------------------------------------
RELAXS.H


------------------------------------------------------------------------------*/

extern  cache const             chRelaxsFlag;
extern  cache const             chRelaxsTariff;
extern  cache const             chRelaxs;



void    InitRelaxs(void);
void    ResetRelaxs(void);
void    DefaultRelaxs(void);

uchar   GetRelaxSize(void);
void    SetRelaxSize(uchar  bSize);

void    GetRelaxDate(uchar  ibRelax);
void    SetRelaxDate(uchar  ibRelax);

uchar   GetMode(time  ti);
