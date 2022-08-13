/*------------------------------------------------------------------------------
correct39_wrapper.h


------------------------------------------------------------------------------*/

#ifndef __CURRENT39_WRAPPER
#define __CURRENT39_WRAPPER


// верхний порог коррекции времени, секунд
#define bMAJORCORRECT_39 900 // 15 минут


#endif



void    Init_Current39(void);

uchar   GetCounter_Correct39(void);

void    SaveFirstDelta_Current39(uint  wDelta);

bool    CheckNextDelta_Current39(uint  wDelta);
void    SaveNextDelta_Current39(void);
