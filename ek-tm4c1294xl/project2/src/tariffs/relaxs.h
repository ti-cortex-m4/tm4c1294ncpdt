/*------------------------------------------------------------------------------
RELAXS.H

 Праздники
------------------------------------------------------------------------------*/

extern  file const              flRelaxsFlag;
extern  file const              flRelaxsTariff;
extern  file const              flRelaxs;



void    InitRelaxs(void);
void    ResetRelaxs(void);
void    DefaultRelaxs(void);

uchar   GetRelaxSize(void);
void    SetRelaxSize(uchar  bSize);

void    GetRelaxDate(uchar  ibRelax);
void    SetRelaxDate(uchar  ibRelax);

uchar   GetMode(time  ti);
