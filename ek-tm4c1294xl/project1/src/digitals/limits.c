/*------------------------------------------------------------------------------
LIMITS.C


------------------------------------------------------------------------------*/

#include    "../main.h"


/*
void    ResetLimits(void)
{
uchar   i;

  boStartCan = TRUE;
  for (i=0; i<bCANALS; i++)
  {
    mpcwStartRelCan[i] = 0;
    mpcwStartAbsCan[i] = 0;
    mpcdwStartAbsCan[i] = 0;
    mpboStartCan[i] = boFalse;
    mpcwStopCan[i] = wHOURS_62-1;                   // самый старый получас
  }
}



bit     UseBounds(void)
{
  return (boStartCan == TRUE);
}



bit     IsLimitsAux(uchar  i)
{
  if ((i == 1) 
   || (i == 2)) return(1);

  return(0);
}



void    NewBoundsRel(uint  i)
{
  LoadCurrDigital(ibDig);      
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1) 
      mpcwStartRelCan[ibCan] = i;
  }
}


void    NewBoundsAbs(uint  i)
{
  LoadCurrDigital(ibDig);      
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    { 
      mpboStartCan[ibCan] = TRUE;
      mpcwStartAbsCan[ibCan] = i;
    } 
  }
}


void    NewBoundsAbs2(ulong  dw)
{
  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    { 
      mpboStartCan[ibCan] = TRUE;
      mpcdwStartAbsCan[ibCan] = dw;
    } 
  }
}
*/

void    NewLimits(void)
{/*
  LoadCurrDigital(ibDig);      
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1) 
    {
      mpcwStartRelCan[ibCan] = 0;
      mpcwStartAbsCan[ibCan] = 0;
      mpcdwStartAbsCan[ibCan] = 0;
      mpboStartCan[ibCan] = boFalse;

      if (UseBounds() && IsLimitsAux(GetDigitalDevice(ibCan)))
      {
        mpcwStopCan[ibCan] = 4 + mpcwStopAuxCan[ibCan];
        if (mpcwStopCan[ibCan] > wHOURS-1) mpcwStopCan[ibCan] = wHOURS-1;
      }
      else
        mpcwStopCan[ibCan] = 4;
    }
  }*/
}


/*
void    MakeLimits(void)
{
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    if (mpcwStopCan[ibCan] < wHOURS-1)
      mpcwStopCan[ibCan]++;          
  }
}



void    ResetLimitsAux(uchar  ibDig) 
{
  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1) 
    {
      mpcwStopAuxCan[ibCan] = 0;
    }
  }
}


void    ResetLimitsAux_All(void)
{
  for (ibCan=0; ibCan<bCANALS; ibCan++)
    ResetLimitsAux(ibCan);
}


void    NextHouLimitsAux(void) 
{
  if (UseBounds())
  {
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      if (IsLimitsAux(GetDigitalDevice(ibCan)))
      {
        mpcwStopAuxCan[ibCan]++;
      }
    }
  }
}
*/
