/*------------------------------------------------------------------------------
DIGITALS_STATUS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



bool                    fStatus;

uint                    wCurr, wPause, wNext;



void    SetCurr(uint  w)
{
  fStatus = 1;
  wCurr = w;
  fStatus = 0;
}


uint    GetCurr(void)
{
uint  w;

  fStatus = 1;
  w = wCurr;
  fStatus = 0;
  return w;
}



void    SetPause(uint  w)
{
  fStatus = 1;
  wPause = w;
  fStatus = 0;
}


uint    GetPause(void)
{
  return wPause;
}



void    SetNext(uint  w)
{
  fStatus = 1;
  wNext = w;
  fStatus = 0;
}


uint    GetNext(void)
{
  return wNext;
}



bool    GetStatus(void)
{
  return fStatus;
}
