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
uchar                   bReviewRepeatBasic; // базовое количество повторов
uchar                   bReviewRepeatWarning; // проверочное количество повторов
uchar                   bReviewRepeatTotal; // максимальное количество повторов
uint                    wReviewWrnPercent;
uint                    wReviewWrnMaximum;

uint                    mcwReviewEvents[REVIEW_EVENTS_SIZE];
uint                    mcwReviewWarnings[REVIEW_EVENTS_SIZE];

cache const             chReviewFlag = {REVIEW_FLAG, &fReviewFlag, sizeof(bool)};
cache const             chReviewCan = {REVIEW_CAN, &mfReviewCan, sizeof(mfReviewCan)};
cache const             chReviewReadId = {REVIEW_READ_ID, &fReviewReadId, sizeof(bool)};
cache const             chReviewRepeatBasic = {REVIEW_REPEAT_BASIC, &bReviewRepeatBasic, sizeof(uchar)};
cache const             chReviewRepeatWarning = {REVIEW_BORDERS, &bReviewRepeatWarning, sizeof(uchar)};
cache const             chReviewRepeatTotal = {REVIEW_REPEAT_TOTAL, &bReviewRepeatTotal, sizeof(uchar)};
cache const             chReviewWrnPercent = {REVIEW_WRN_PERCENT, &wReviewWrnPercent, sizeof(uint)};
cache const             chReviewWrnMaximum = {REVIEW_WRN_MAXIMUM, &wReviewWrnMaximum, sizeof(uint)};



void InitReview(void)
{
  LoadCacheBool(&chReviewFlag, false);
  LoadCache(&chReviewCan);
  LoadCacheBool(&chReviewReadId, false);
  LoadCacheChar(&chReviewRepeatBasic, REVIEW_REPEAT_BASIC_MIN, REVIEW_REPEAT_BASIC_MAX, REVIEW_REPEAT_BASIC_DEF);
  LoadCacheChar(&chReviewRepeatWarning, REVIEW_BORDERS_MIN, REVIEW_BORDERS_MAX, REVIEW_BORDERS_DEF);
  LoadCacheChar(&chReviewRepeatTotal, REVIEW_REPEAT_TOTAL_MIN, REVIEW_REPEAT_TOTAL_MAX, REVIEW_REPEAT_TOTAL_DEF);
  LoadCacheInt(&chReviewWrnPercent, REVIEW_WRN_PERCENT_MIN, REVIEW_WRN_PERCENT_MAX, REVIEW_WRN_PERCENT_DEF);
  LoadCacheInt(&chReviewWrnMaximum, REVIEW_WRN_MAXIMUM_MIN, REVIEW_WRN_MAXIMUM_MAX, REVIEW_WRN_MAXIMUM_DEF);

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
    SaveCacheChar(&chReviewRepeatBasic, REVIEW_REPEAT_BASIC_DEF);
    SaveCacheChar(&chReviewRepeatWarning, REVIEW_BORDERS_DEF);
    SaveCacheChar(&chReviewRepeatTotal, REVIEW_REPEAT_TOTAL_DEF);
    SaveCacheInt(&chReviewWrnPercent, REVIEW_WRN_PERCENT_DEF);
    SaveCacheInt(&chReviewWrnMaximum, REVIEW_WRN_MAXIMUM_DEF);
  }
}
