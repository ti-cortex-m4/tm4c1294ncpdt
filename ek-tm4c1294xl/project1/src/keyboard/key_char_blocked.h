/*------------------------------------------------------------------------------
KEY_CHAR_BLOCKED,H


------------------------------------------------------------------------------*/

#include "../include/programs.h"



extern  char                    szCharLimits[bDISPLAY + bMARGIN];



void    key_SetCharBlocked(file const  *pflFile, char const  *pszSlide[], uchar  bMin, uchar  bMax, bool  fBlocked, uint  wProgram);
