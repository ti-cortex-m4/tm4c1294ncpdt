/*------------------------------------------------------------------------------
RELAXS.H

 Подпрограммы управления праздниками
------------------------------------------------------------------------------*/

#include        "../main.h"



uchar   GetRelaxSize(void);
void    SetRelaxSize(uchar  bSize);

void    GetRelaxDate(uchar  ibRelax);
void    SetRelaxDate(uchar  ibRelax);

void    DefaultRelaxs(void);
void    ResetRelaxs(void);

uchar   GetModeAlt(void);

void    ShowModeName(uchar  ibMode);
void    ShowRelax(uchar  ibRelax);
