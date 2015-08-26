/*------------------------------------------------------------------------------
KEY_INT_BLOCKED,H


------------------------------------------------------------------------------*/

#include "../../include/programs.h"



extern  char                    szNumberLimits[bDISPLAY + bMARGIN];



void    key_SetIntBlocked(cache const  *pch, char const  *pszSlide[], uint  wMin, uint  wMax, bool  fNonBlocked, uint  wProgram);
