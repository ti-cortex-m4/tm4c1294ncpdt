/*------------------------------------------------------------------------------
review_out.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
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
  wSize += PushIntBig(wReviewWrnPercent);
  wSize += PushIntBig(wReviewWrnMaximum);

  wSize += PushBoolArray(mfReviewCan, bCANALS);

  wSize += PushIntBigArray(mcwReviewEvents, REVIEW_EVENTS_SIZE);
  wSize += PushIntBigArray(mcwReviewWarnings, REVIEW_EVENTS_SIZE);

  wSize += PushBool(boShortProfileC);

  Output(wSize);
}
