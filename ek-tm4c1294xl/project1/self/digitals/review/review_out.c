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

  wSize += Push(&mcwReviewWrn, sizeof(mcwReviewWrn));

  Output(wSize);
}
