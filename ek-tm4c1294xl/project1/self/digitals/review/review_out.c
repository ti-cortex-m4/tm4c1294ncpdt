/*------------------------------------------------------------------------------
review_out.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports_common.h"
#include "../../serial/ports.h"
#include "review.h"
#include "review_out.h"



void OutReview(void)
{
  InitPushCRC();
  uint wSize = 0;

  wSize += PushChar(0); // версия запроса
  wSize += PushBool(fReviewFlag);
  wSize += PushBool(fReviewReadId);
  wSize += PushChar(bReviewRepeats);
  wSize += PushChar(bReviewBorders);
  wSize += PushChar(bReviewMargins);
  wSize += PushChar(bReviewWrnTrend);
  wSize += PushIntBig(wReviewWrnTop);

  uchar i;
  for (i=0; i<16; i++)
    wSize += PushIntBig(mcwReviewEvents[i]);

  for (i=0; i<16; i++)
    wSize += PushIntBig(mcwReviewWarnings[i]);

  Output(wSize);
}
