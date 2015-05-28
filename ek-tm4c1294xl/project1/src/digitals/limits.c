/*------------------------------------------------------------------------------
LIMITS.C


------------------------------------------------------------------------------*/

#include    "../main.h"
#include    "../memory/mem_limits.h"
#include    "../digitals/digitals.h"
#include    "../devices/devices.h"
#include    "../flash/files.h"
#include    "limits.h"



file const              flUseBounds = {USE_BOUNDS, &boUseBounds, sizeof(bool)};

file const              flStartRelCan = {START_REL_CAN, &mpcwStartRelCan, sizeof(mpcwStartRelCan)};
file const              flStartAbs16Can = {START_ABS16_CAN, &mpcwStartAbs16Can, sizeof(mpcwStartAbs16Can)};
file const              flStartAbs32Can = {START_ABS32_CAN, &mpcdwStartAbs32Can, sizeof(mpcdwStartAbs32Can)};
file const              flStartCan = {START_CAN, &mpboStartCan, sizeof(mpboStartCan)};
file const              flStopCan = {STOP_CAN, &mpcwStopCan, sizeof(mpcwStopCan)};
file const              flStopAuxCan = {STOP_AUX_CAN, &mpcwStopAuxCan, sizeof(mpcwStopAuxCan)};



void    InitLimits(void)
{
  LoadFile(&flUseBounds);

  LoadFile(&flStartRelCan);
  LoadFile(&flStartAbs16Can);
  LoadFile(&flStartAbs32Can);
  LoadFile(&flStartCan);
  LoadFile(&flStopCan);
  LoadFile(&flStopAuxCan);
}


void    ResetLimits(void)
{

	boUseBounds = true;
  SaveFile(&flUseBounds);

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

  SaveFile(&flStartRelCan);
  SaveFile(&flStartAbs16Can);
  SaveFile(&flStartAbs32Can);
  SaveFile(&flStartCan);
  SaveFile(&flStopCan);
  SaveFile(&flStopAuxCan);
}



bool    UseBounds(void)
{
  return boUseBounds == true;
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
    if (CompareCurrPrevLines(ibDig, c) == true)
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
    if (CompareCurrPrevLines(ibDig, c) == true)
    { 
      mpboStartCan[c] = true;
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
    if (CompareCurrPrevLines(ibDig, c) == true)
    { 
      mpboStartCan[c] = true;
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
    if (CompareCurrPrevLines(ibDig, c) == true)
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
    if (CompareCurrPrevLines(ibDig, c) == true)
    {
      mpcwStopAuxCan[c] = 0;
    }
  }

  SaveFile(&flStopAuxCan);
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

    SaveFile(&flStopAuxCan);
  }
}
