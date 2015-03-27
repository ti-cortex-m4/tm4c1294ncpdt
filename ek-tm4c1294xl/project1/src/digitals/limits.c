/*------------------------------------------------------------------------------
LIMITS.C


------------------------------------------------------------------------------*/

#include    "../main.h"
#include    "../memory/mem_limits.h"
#include    "../digitals/digitals.h"
#include    "../devices/devices.h"
#include    "../flash/files.h"
#include    "limits.h"



file const              flUseBounds = {FLS_USE_BOUNDS, &boUseBounds, sizeof(boolean)};

file const              flStartRelCan = {FLS_START_REL_CAN, &mpcwStartRelCan, sizeof(mpcwStartRelCan)};
file const              flStartAbs16Can = {FLS_START_ABS16_CAN, &mpcwStartAbs16Can, sizeof(mpcwStartAbs16Can)};
file const              flStartAbs32Can = {FLS_START_ABS32_CAN, &mpcdwStartAbs32Can, sizeof(mpcdwStartAbs32Can)};
file const              flStartCan = {FLS_START_CAN, &mpboStartCan, sizeof(mpboStartCan)};
file const              flStopCan = {FLS_STOP_CAN, &mpcwStopCan, sizeof(mpcwStopCan)};



void    InitLimits(void)
{
  LoadFile(&flUseBounds);

  LoadFile(&flStartRelCan);
  LoadFile(&flStartAbs16Can);
  LoadFile(&flStartAbs32Can);
  LoadFile(&flStartCan);
  LoadFile(&flStopCan);
}


void    ResetLimits(void)
{

	boUseBounds = TRUE;
  SaveFile(&flUseBounds);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpcwStartRelCan[c] = 0;
    mpcwStartAbs16Can[c] = 0;
    mpcdwStartAbs32Can[c] = 0;
    mpboStartCan[c] = FALSE;
    mpcwStopCan[c] = wHOURS_62-1; // самый старый получас
  }

  SaveFile(&flStartRelCan);
  SaveFile(&flStartAbs16Can);
  SaveFile(&flStartAbs32Can);
  SaveFile(&flStartCan);
  SaveFile(&flStopCan);
}



bool    UseBounds(void)
{
  return boUseBounds == TRUE;
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
    if (CompareCurrPrevLines(ibDig, c) == 1)
    {
      mpcwStartRelCan[c] = wRel;
    }
  }

  SaveFile(&flStartRelCan);
}


void    NewBoundsAbs16(uint  wAbs)
{
  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == 1)
    { 
      mpboStartCan[c] = TRUE;
      mpcwStartAbs16Can[c] = wAbs;
    } 
  }

  SaveFile(&flStartCan);
  SaveFile(&flStartAbs16Can);
}


void    NewBoundsAbs32(ulong  dwAbs)
{
  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == 1)
    { 
      mpboStartCan[c] = TRUE;
      mpcdwStartAbs32Can[c] = dwAbs;
    } 
  }

  SaveFile(&flStartCan);
  SaveFile(&flStartAbs32Can);
}


void    NewLimits(void)
{
  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == 1)
    {
      mpcwStartRelCan[c] = 0;
      mpcwStartAbs16Can[c] = 0;
      mpcdwStartAbs32Can[c] = 0;
      mpboStartCan[c] = FALSE;

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

  SaveFile(&flStartRelCan);
  SaveFile(&flStartAbs16Can);
  SaveFile(&flStartAbs32Can);
  SaveFile(&flStartCan);
  SaveFile(&flStopCan);
}



void    MakeLimits(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (mpcwStopCan[c] < wHOURS-1)
      mpcwStopCan[c]++;
  }

  SaveFile(&flStopCan);
}



void    ResetLimitsAux(uchar  ibDig) 
{
  LoadCurrDigital(ibDig);

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    LoadPrevDigital(c);
    if (CompareCurrPrevLines(ibDig, c) == 1)
    {
      mpcwStopAuxCan[c] = 0;
    }
  }
}


void    ResetLimitsAux_All(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
    ResetLimitsAux(c);
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
  }
}
