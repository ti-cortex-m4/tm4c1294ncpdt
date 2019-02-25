/*------------------------------------------------------------------------------
LIMITS!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_limits.h"
#include "../digitals/digitals.h"
#include "../devices/devices.h"
#include "../nvram/cache.h"
#include "limits.h"



bool    ActualLine34(uchar  ibDig, uchar  ibCan);



cache const             chUseBounds = {USE_BOUNDS, &fUseBounds, sizeof(bool)};

cache const             chStartRelCan = {START_REL_CAN, &mpcwStartRelCan, sizeof(mpcwStartRelCan)};
cache const             chStartAbs16Can = {START_ABS16_CAN, &mpcwStartAbs16Can, sizeof(mpcwStartAbs16Can)};
cache const             chStartAbs32Can = {START_ABS32_CAN, &mpcdwStartAbs32Can, sizeof(mpcdwStartAbs32Can)};
cache const             chStartCan = {START_CAN, &mpboStartCan, sizeof(mpboStartCan)};
cache const             chStopCan = {STOP_CAN, &mpcwStopCan, sizeof(mpcwStopCan)};
cache const             chStopAuxCan = {STOP_AUX_CAN, &mpcwStopAuxCan, sizeof(mpcwStopAuxCan)};



void    InitLimits(void)
{
  LoadCache(&chUseBounds);

  LoadCache(&chStartRelCan);
  LoadCache(&chStartAbs16Can);
  LoadCache(&chStartAbs32Can);
  LoadCache(&chStartCan);
  LoadCache(&chStopCan);
  LoadCache(&chStopAuxCan);
}


void    ResetLimits(void)
{
  fUseBounds = true;
  SaveCache(&chUseBounds);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpcwStartRelCan[c] = 0;
    mpcwStartAbs16Can[c] = 0;
    mpcdwStartAbs32Can[c] = 0;
    mpboStartCan[c] = false;
    mpcwStopCan[c] = wHOURS_62-1; // самый старый получас
    mpcwStopAuxCan[c] = 0;
  }

  SaveCache(&chStartRelCan);
  SaveCache(&chStartAbs16Can);
  SaveCache(&chStartAbs32Can);
  SaveCache(&chStartCan);
  SaveCache(&chStopCan);
  SaveCache(&chStopAuxCan);
}



bool    UseBounds(void)
{
  return fUseBounds == true;
}



bool    IsLimitsAux(uchar  ibDev)
{
  if ((ibDev == 1) 
   || (ibDev == 2)) return(1);

  return(0);
}



void    NewBoundsRel(uint  wRel)
{
  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) && ActualLine34(ibDig, c))
    {
      mpcwStartRelCan[c] = wRel;
    }
  }

  SaveCache(&chStartRelCan);
}


void    NewBoundsAbs16(uint  wAbs)
{
  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == true)
    { 
      mpboStartCan[c] = true;
      mpcwStartAbs16Can[c] = wAbs;
    } 
  }

  SaveCache(&chStartCan);
  SaveCache(&chStartAbs16Can);
}


void    NewBoundsAbs32(ulong  dwAbs)
{
  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == true)
    { 
      mpboStartCan[c] = true;
      mpcdwStartAbs32Can[c] = dwAbs;
    } 
  }

  SaveCache(&chStartCan);
  SaveCache(&chStartAbs32Can);
}


void    NewLimits(void)
{
  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) && ActualLine34(ibDig, c))
    {
      mpcwStartRelCan[c] = 0;
      mpcwStartAbs16Can[c] = 0;
      mpcdwStartAbs32Can[c] = 0;
      mpboStartCan[c] = false;

      if (UseBounds() && IsLimitsAux(GetDigitalDevice(c)))
      {
        mpcwStopCan[c] = 4 + mpcwStopAuxCan[c];
        if (mpcwStopCan[c] > wHOURS-1) mpcwStopCan[c] = wHOURS-1;
      }
      else
      {
        mpcwStopCan[c] = 4;
      }
    }
  }

  SaveCache(&chStartRelCan);
  SaveCache(&chStartAbs16Can);
  SaveCache(&chStartAbs32Can);
  SaveCache(&chStartCan);
  SaveCache(&chStopCan);
}



void    MakeLimits(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (mpcwStopCan[c] < wHOURS-1)
      mpcwStopCan[c]++;
  }

  SaveCache(&chStopCan);
}



void    ResetLimitsAux(uchar  ibDig) 
{
  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == true)
    {
      mpcwStopAuxCan[c] = 0;
    }
  }

  SaveCache(&chStopAuxCan);
}


void    NextHouLimitsAux(void) 
{
  if (UseBounds())
  {
    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if (IsLimitsAux(GetDigitalDevice(c)))
      {
        mpcwStopAuxCan[c]++;
      }
    }

    SaveCache(&chStopAuxCan);
  }
}
