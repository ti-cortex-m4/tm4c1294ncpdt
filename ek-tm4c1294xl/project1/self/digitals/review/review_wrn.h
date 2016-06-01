/*------------------------------------------------------------------------------
review_wrn.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW_WRN
#define __REVIEW_WRN

typedef enum
{
  REVIEW_WRN_OK             = 0,
  REVIEW_WRN_ZERO           = 1,
  REVIEW_WRN_REPEAT         = 2,
  REVIEW_WRN_TOP            = 3,
  REVIEW_WRN_TREND_TOP      = 4,
  REVIEW_WRN_TREND_BOTTOM   = 5
} review_wrn;



bool WrnReviewBuff(uchar  bSize);

#endif
