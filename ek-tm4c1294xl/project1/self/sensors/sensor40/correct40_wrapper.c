/*------------------------------------------------------------------------------
correct40_wrapper.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "correct40.h"
#include "correct40_wrapper.h"



static uint             cwCorrects40;
static uint             wDeltaOld40;
static uint             wDeltaNew40;



void    Init_Correct40(void)
{
  cwCorrects40 = 0;
  wDeltaOld40 = 0;
  wDeltaNew40 = 0;
}



uchar   GetCounter_Correct40(void)
{
  return cwCorrects40;
}



void    SaveFirstDelta_Current40(uint  wDelta)
{
  cwCorrects40++;
  wDeltaOld40 = wDelta;
}



bool    CheckNextDelta_Current40(uint  wDelta)
{
  wDeltaNew40 = wDelta;
  return (wDeltaNew40 < wDeltaOld40) && (cwCorrects40 < 300);
}


void    SaveNextDelta_Current40(void)
{
  cwCorrects40++;
  wDeltaOld40 = wDeltaNew40;
}
