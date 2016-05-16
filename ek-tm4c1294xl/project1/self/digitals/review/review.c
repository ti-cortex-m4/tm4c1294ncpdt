/*------------------------------------------------------------------------------
review.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "review.h"



bool                    fReviewReadId;
uchar                   bReviewRepeats;

cache const             chReviewReadId = {REVIEW_READ_ID, &fReviewReadId, sizeof(bool)};
cache const             chReviewRepeats = {REVIEW_REPEATS, &bReviewRepeats, sizeof(uchar)};



void    InitReview(void)
{
  LoadCacheBool(&chReviewReadId, false);
  LoadCacheChar(&chReviewRepeats, 1, 5, 1);
}


void    ResetReview(void)
{
  SaveCacheBool(&chReviewReadId, false);
  SaveCacheChar(&chReviewRepeats, 1);
}
