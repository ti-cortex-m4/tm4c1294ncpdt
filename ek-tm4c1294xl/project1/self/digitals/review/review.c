/*------------------------------------------------------------------------------
review.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "review.h"



bool                    fReviewReadId;
uchar                   bReviewRepeats;
uchar                   bReviewMargins;

cache const             chReviewReadId = {REVIEW_READ_ID, &fReviewReadId, sizeof(bool)};
cache const             chReviewRepeats = {REVIEW_REPEATS, &bReviewRepeats, sizeof(uchar)};
cache const             chReviewMargins = {REVIEW_MARGINS, &bReviewMargins, sizeof(uchar)};



void InitReview(void)
{
  LoadCacheBool(&chReviewReadId, false);
  LoadCacheChar(&chReviewRepeats, REVIEW_REPEATS_MIN, REVIEW_REPEATS_MAX, REVIEW_REPEATS_MIN);
  LoadCacheChar(&chReviewMargins, REVIEW_MARGINS_MIN, REVIEW_MARGINS_MAX, REVIEW_MARGINS_MIN);
}


void ResetReview(void)
{
  SaveCacheBool(&chReviewReadId, false);
  SaveCacheChar(&chReviewRepeats, REVIEW_REPEATS_MIN);
  SaveCacheChar(&chReviewMargins, REVIEW_MARGINS_MIN);
}
