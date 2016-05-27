/*------------------------------------------------------------------------------
review.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "review.h"



bool                    fReviewFlag;
bool                    fReviewReadId;
uchar                   bReviewRepeats;
uchar                   bReviewMargins;
uchar                   bReviewWrnPercent;
uint                    wReviewWrnTop;

cache const             chReviewFlag = {REVIEW_FLAG, &fReviewFlag, sizeof(bool)};
cache const             chReviewReadId = {REVIEW_READ_ID, &fReviewReadId, sizeof(bool)};
cache const             chReviewRepeats = {REVIEW_REPEATS, &bReviewRepeats, sizeof(uchar)};
cache const             chReviewMargins = {REVIEW_MARGINS, &bReviewMargins, sizeof(uchar)};
cache const             chReviewWrnPercent = {REVIEW_WRN_RERCENT, &bReviewWrnPercent, sizeof(uchar)};
cache const             chReviewWrnTop = {REVIEW_WRN_TOP, &wReviewWrnTop, sizeof(uint)};



void InitReview(void)
{
  LoadCacheBool(&chReviewFlag, false);
  LoadCacheBool(&chReviewReadId, false);
  LoadCacheChar(&chReviewRepeats, REVIEW_REPEATS_MIN, REVIEW_REPEATS_MAX, REVIEW_REPEATS_MIN);
  LoadCacheChar(&chReviewMargins, REVIEW_MARGINS_MIN, REVIEW_MARGINS_MAX, REVIEW_MARGINS_MIN);
}


void ResetReview(bool  fFull)
{
  if (fFull)
  {
    SaveCacheBool(&chReviewFlag, false);
    SaveCacheBool(&chReviewReadId, false);
    SaveCacheChar(&chReviewRepeats, REVIEW_REPEATS_MIN);
    SaveCacheChar(&chReviewMargins, REVIEW_MARGINS_MIN);
  }
}
