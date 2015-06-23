/*------------------------------------------------------------------------------
KEY_CHAR_BLOCKED,H


------------------------------------------------------------------------------*/

#include "../include/programs.h"



extern  char                    szCharLimits[bDISPLAY + bMARGIN];



void    key_SetCharBlocked(cache const  *pch, char const  *pszSlide[], uchar  bMin, uchar  bMax, bool  fBlocked, uint  wProgram);
