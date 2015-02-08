/*------------------------------------------------------------------------------
RELAXS.H

 Подпрограммы управления праздниками
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

uchar   GetModeAlt(void);

void    ShowModeName(uchar  ibMode);
void    ShowRelax(uchar  ibRelax);
