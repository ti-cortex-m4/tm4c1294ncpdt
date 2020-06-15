/*------------------------------------------------------------------------------
DIGITALS_STATUS!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "digitals_status.h"



volatile bool           fStatus;

volatile device         deCurr, dePause, deNext;



void    SetCurr(device  de)
{
  fStatus = 1;
  deCurr = de;
  fStatus = 0;
}


device  GetCurr(void)
{
device de;

  fStatus = 1;
  de = deCurr;
  fStatus = 0;
  return de;
}



void    SetPause(device  de)
{
  fStatus = 1;
  dePause = de;
  fStatus = 0;
}


device  GetPause(void)
{
  return dePause;
}



void    SetNext(device  de)
{
  fStatus = 1;
  deNext = de;
  fStatus = 0;
}


device  GetNext(void)
{
  return deNext;
}



bool    GetStatus(void)
{
  return fStatus;
}
