/*------------------------------------------------------------------------------
correct39_wrapper.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "correct40.h"
#include "correct39_wrapper.h"



static uint             cwCorrects39;
static uint             wDeltaOld39;
static uint             wDeltaNew39;



void    Init_Correct39(void)
{
  cwCorrects39 = 0;
  wDeltaOld39 = 0;
  wDeltaNew39 = 0;
}



uchar   GetCounter_Correct39(void)
{
  return cwCorrects39;
}



void    SaveFirstDelta_Current39(uint  wDelta)
{
  cwCorrects39++;
  wDeltaOld39 = wDelta;
}



bool    CheckNextDelta_Current39(uint  wDelta)
{
  wDeltaNew39 = wDelta;
  return (wDeltaNew39 < wDeltaOld39) && (cwCorrects39 < 300);
}


void    SaveNextDelta_Current39(void)
{
  cwCorrects39++;
  wDeltaOld39 = wDeltaNew39;
}
