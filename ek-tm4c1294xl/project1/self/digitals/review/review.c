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
uchar                   bReviewBorders;
uchar                   bReviewMargins;
uchar                   bReviewWrnTrend;
uint                    wReviewWrnTop;

uint                    mcwReviewEvent[16];
uint                    mcwReviewWarning[16];

cache const             chReviewFlag = {REVIEW_FLAG, &fReviewFlag, sizeof(bool)};
cache const             chReviewReadId = {REVIEW_READ_ID, &fReviewReadId, sizeof(bool)};
cache const             chReviewRepeats = {REVIEW_REPEATS, &bReviewRepeats, sizeof(uchar)};
cache const             chReviewBorders = {REVIEW_BORDERS, &bReviewBorders, sizeof(uchar)};
cache const             chReviewMargins = {REVIEW_MARGINS, &bReviewMargins, sizeof(uchar)};
cache const             chReviewWrnTrend = {REVIEW_WRN_TREND, &bReviewWrnTrend, sizeof(uchar)};
cache const             chReviewWrnTop = {REVIEW_WRN_TOP, &wReviewWrnTop, sizeof(uint)};



void InitReview(void)
{
  LoadCacheBool(&chReviewFlag, false);
  LoadCacheBool(&chReviewReadId, false);
  LoadCacheChar(&chReviewRepeats, REVIEW_REPEATS_MIN, REVIEW_REPEATS_MAX, REVIEW_REPEATS_DEF);
  LoadCacheChar(&chReviewBorders, REVIEW_BORDERS_MIN, REVIEW_BORDERS_MAX, REVIEW_BORDERS_DEF);
  LoadCacheChar(&chReviewMargins, REVIEW_MARGINS_MIN, REVIEW_MARGINS_MAX, REVIEW_MARGINS_DEF);
  LoadCacheChar(&chReviewWrnTrend, REVIEW_WRN_TREND_MIN, REVIEW_WRN_TREND_MAX, REVIEW_WRN_TREND_DEF);
  LoadCacheInt(&chReviewWrnTop, REVIEW_WRN_TOP_MIN, REVIEW_WRN_TOP_MAX, REVIEW_WRN_TOP_DEF);

  memset(&mcwReviewEvent, 0, sizeof(mcwReviewEvent));
  memset(&mcwReviewWarning, 0, sizeof(mcwReviewWarning));
}


void ResetReview(bool  fFull)
{
  if (fFull)
  {
    SaveCacheBool(&chReviewFlag, false);
    SaveCacheBool(&chReviewReadId, false);
    SaveCacheChar(&chReviewRepeats, REVIEW_REPEATS_DEF);
    SaveCacheChar(&chReviewBorders, REVIEW_BORDERS_DEF);
    SaveCacheChar(&chReviewMargins, REVIEW_MARGINS_DEF);
    SaveCacheChar(&chReviewWrnTrend, REVIEW_WRN_TREND_DEF);
    SaveCacheInt(&chReviewWrnTop, REVIEW_WRN_TOP_DEF);
  }
}
