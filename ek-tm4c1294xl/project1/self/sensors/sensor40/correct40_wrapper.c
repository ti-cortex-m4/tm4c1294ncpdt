/*------------------------------------------------------------------------------
correct40_wrapper.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "correct40.h"
#include "correct40_wrapper.h"



static uint             cwCorrects;

static uint             wDeltaOld;
static uint             wDeltaNew;



void    Init_Correct40(void)
{
  cwCorrects = 0;

  wDeltaOld = 0;
  wDeltaNew = 0;
}



uchar   GetCounter_Correct40(void)
{
  return cwCorrects;
}



void    SaveFirstDelta_Current40(uint  wDelta)
{
  cwCorrects++;
  wDeltaOld = wDelta;
}



bool    CheckNextDelta_Current40(uint  wDelta)
{
  wDeltaNew = wDelta;
  return (wDeltaNew < wDeltaOld) && (cwCorrects < 300);
}


void    SaveNextDelta_Current40(void)
{
  cwCorrects++;
  wDeltaOld = wDeltaNew;
}
