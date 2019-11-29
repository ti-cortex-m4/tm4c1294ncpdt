/*------------------------------------------------------------------------------
timer35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "timer35.h"



static volatile     bool        fEnabled = true;
static volatile     uint        wTimer = 0;



void    SetTimer35(uint  w)
{
  fEnabled = false;
  wTimer = w;
  fEnabled = true;
}


uint    GetTimer35(void)
{
  return wTimer;
}



void    Timer35_1Hz(void)
{
  if (fEnabled)
  {
    wTimer++;
  }
}
