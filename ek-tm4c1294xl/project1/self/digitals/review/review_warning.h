/*------------------------------------------------------------------------------
review_warning.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW_WARNING
#define __REVIEW_WARNING

typedef enum
{
  REVIEW_WRN_OK             = 0,
  REVIEW_WRN_ZERO           = 1,
  REVIEW_WRN_REPEAT         = 2,
  REVIEW_WRN_TOP            = 3,
  REVIEW_WRN_PERCENT_TOP      = 4,
  REVIEW_WRN_PERCENT_BOTTOM   = 5
} review_wrn;



bool WarningReviewBuff(uchar  bSize);

#endif
