/*------------------------------------------------------------------------------
correct40_wrapper.h


------------------------------------------------------------------------------*/

void    Init_Correct40(void);

uchar   GetCounter_Correct40(void);

void    SaveFirstDelta_Current40(uint  wDelta);

bool    CheckNextDelta_Current40(uint  wDelta);
void    SaveNextDelta_Current40(void);
