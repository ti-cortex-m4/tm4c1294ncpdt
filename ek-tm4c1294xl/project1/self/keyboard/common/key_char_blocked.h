/*------------------------------------------------------------------------------
KEY_CHAR_BLOCKED,H


------------------------------------------------------------------------------*/

#include "../../include/programs.h"



extern  char                    szNumberLimits[bDISPLAY + bMARGIN];



void    key_SetCharBlocked(cache const  *pch, char const  *pszSlide[], uchar  bMin, uchar  bMax, bool  fNonBlocked, uint  wProgram);
