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
cache const             chbReviewRepeats = {REVIEW_REPEATS, &bReviewRepeats, sizeof(uchar)};



void    InitReview(void)
{
  LoadCacheBool(&chReviewReadId, false);
  LoadCacheChar(&chbReviewRepeats, 0, 4, 0);
}


void    ResetReview(void)
{
  SaveCacheBool(&chReviewReadId, false);
  SaveCacheChar(&chbReviewRepeats, 0);
}
