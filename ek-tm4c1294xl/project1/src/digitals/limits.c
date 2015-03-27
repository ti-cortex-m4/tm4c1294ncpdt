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

  uchar ibCan;
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1)
      mpcwStartRelCan[ibCan] = wRel;
  }

  SaveFile(&flStartRelCan);
}


void    NewBoundsAbs16(uint  wAbs)
{
  LoadCurrDigital(ibDig);

  uchar ibCan;
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1)
    { 
      mpboStartCan[ibCan] = TRUE;
      mpcwStartAbs16Can[ibCan] = wAbs;
    } 
  }

  SaveFile(&flStartCan);
  SaveFile(&flStartAbs16Can);
}


void    NewBoundsAbs32(ulong  dwAbs)
{
  LoadCurrDigital(ibDig);

  uchar ibCan;
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines(ibDig, ibCan) == 1)
    { 
      mpboStartCan[ibCan] = TRUE;
      mpcdwStartAbs32Can[ibCan] = dwAbs;
    } 
  }

  SaveFile(&flStartCan);
  SaveFile(&flStartAbs32Can);
}


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
      mpboStartCan[ibCan] = FALSE;

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
*/


void    ResetLimitsAux(uchar  ibDig) 
{/*
  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1) 
    {
      mpcwStopAuxCan[ibCan] = 0;
    }
  }*/
}

/*
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
