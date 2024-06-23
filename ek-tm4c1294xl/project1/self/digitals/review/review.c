/*------------------------------------------------------------------------------
review.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "review.h"



bool                    fReviewFlag;
bool                    mfReviewCan[bCANALS];
bool                    fReviewReadId;
uchar                   bReviewRepeats;
uchar                   bReviewBorders;
uchar                   bReviewMargins;
uint                    wReviewWrnPercent;
uint                    wReviewWrnTop;

uint                    mcwReviewEvents[REVIEW_EVENTS_SIZE];
uint                    mcwReviewWarnings[REVIEW_EVENTS_SIZE];

cache const             chReviewFlag = {REVIEW_FLAG, &fReviewFlag, sizeof(bool)};
cache const             chReviewCan = {REVIEW_CAN, &mfReviewCan, sizeof(mfReviewCan)};
cache const             chReviewReadId = {REVIEW_READ_ID, &fReviewReadId, sizeof(bool)};
cache const             chReviewRepeats = {REVIEW_REPEATS, &bReviewRepeats, sizeof(uchar)};
cache const             chReviewBorders = {REVIEW_BORDERS, &bReviewBorders, sizeof(uchar)};
cache const             chReviewMargins = {REVIEW_MARGINS, &bReviewMargins, sizeof(uchar)};
cache const             chReviewWrnPercent = {REVIEW_WRN_PERCENT, &wReviewWrnPercent, sizeof(uint)};
cache const             chReviewWrnTop = {REVIEW_WRN_TOP, &wReviewWrnTop, sizeof(uint)};



void InitReview(void)
{
  LoadCacheBool(&chReviewFlag, false);
  LoadCache(&chReviewCan);
  LoadCacheBool(&chReviewReadId, false);
  LoadCacheChar(&chReviewRepeats, REVIEW_REPEATS_MIN, REVIEW_REPEATS_MAX, REVIEW_REPEATS_DEF);
  LoadCacheChar(&chReviewBorders, REVIEW_BORDERS_MIN, REVIEW_BORDERS_MAX, REVIEW_BORDERS_DEF);
  LoadCacheChar(&chReviewMargins, REVIEW_MARGINS_MIN, REVIEW_MARGINS_MAX, REVIEW_MARGINS_DEF);
  LoadCacheInt(&chReviewWrnPercent, REVIEW_WRN_PERCENT_MIN, REVIEW_WRN_PERCENT_MAX, REVIEW_WRN_PERCENT_DEF);
  LoadCacheInt(&chReviewWrnTop, REVIEW_WRN_TOP_MIN, REVIEW_WRN_TOP_MAX, REVIEW_WRN_TOP_DEF);

  memset(&mcwReviewEvents, 0, sizeof(mcwReviewEvents));
  memset(&mcwReviewWarnings, 0, sizeof(mcwReviewWarnings));
}


void ResetReview(bool  fFull)
{
  if (fFull)
  {
    SaveCacheBool(&chReviewFlag, false);

    uchar c;
    for (c=0; c<bCANALS; c++)
      mfReviewCan[c] = false;

    SaveCache(&chReviewCan);

    SaveCacheBool(&chReviewReadId, false);
    SaveCacheChar(&chReviewRepeats, REVIEW_REPEATS_DEF);
    SaveCacheChar(&chReviewBorders, REVIEW_BORDERS_DEF);
    SaveCacheChar(&chReviewMargins, REVIEW_MARGINS_DEF);
    SaveCacheInt(&chReviewWrnPercent, REVIEW_WRN_PERCENT_DEF);
    SaveCacheInt(&chReviewWrnTop, REVIEW_WRN_TOP_DEF);
  }
}
