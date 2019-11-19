/*------------------------------------------------------------------------------
timer35.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "timer35.h"



static volatile     bool        f = true;
static volatile     uint        wTimer = 0;



void    SetTimer35(uint  w)
{
  f = false;
  wTimer = w;
  f = true;
}


uint    GetTimer35(void)
{
  return wTimer;
}



void    Timer35_10Hz(void)
{
  if (f)
  {
    wTimer++;
  }
}
