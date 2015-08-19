/*------------------------------------------------------------------------------
KEY_INT_BLOCKED,H


------------------------------------------------------------------------------*/

#include "../include/programs.h"



extern  char                    szCharLimits[bDISPLAY + bMARGIN];



void    key_SetCharBlocked(cache const  *pch, char const  *pszSlide[], uint  wMin, uint  wMax, bool  fBlocked, uint  wProgram);
