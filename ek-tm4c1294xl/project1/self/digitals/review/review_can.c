/*------------------------------------------------------------------------------
review_can.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/digitals.h"
#include "review.h"
#include "review_can.h"



uchar                   mbRevewCanIdx[4];



static uchar RevewCanIdx(uchar  ibDig, uchar  ibLine)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if ((GetDigitalPort(ibDig)    == GetDigitalPort(c))    &&
        (GetDigitalPhone(ibDig)   == GetDigitalPhone(c))   &&
        (GetDigitalDevice(ibDig)  == GetDigitalDevice(c))  &&
        (GetDigitalAddress(ibDig) == GetDigitalAddress(c)) &&
        (ibLine                   == GetDigitalLine(c))) return c;
  }

  return 0xFF;
}


void StartReviewCan(uchar  ibDig)
{
  uchar i;
  for (i=0; i<4; i++)
    mbRevewCanIdx[i] = RevewCanIdx(ibDig, i);
}
