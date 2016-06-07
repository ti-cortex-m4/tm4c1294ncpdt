/*------------------------------------------------------------------------------
review_line.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "review.h"
#include "review_line.h"



uchar                   mbRevewLine[4];



static uchar GetIdx(uchar  ibLine)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((GetDigitalPort(ibDig)    == GetDigitalPort(ibCan))   &&
        (GetDigitalPhone(ibDig)   == GetDigitalPhone(ibCan))  &&
        (GetDigitalDevice(ibDig)  == GetDigitalDevice(ibCan))  &&
        (GetDigitalAddress(ibDig) == GetDigitalAddress(ibCan)) &&
        (GetDigitalLine(ibDig)    == GetDigitalLine(ibCan))) return c;
  }

  return 0xFF;
}


void StartReviewLine(void)
{
  uchar i;
  for i=0; i<4; i++)
    mbRevewLine[i] = GetIdx(i);
}
