/*------------------------------------------------------------------------------
review_core.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW_CORE
#define __REVIEW_CORE

typedef enum
{
  REVIEW_REPEAT         = 0,
  REVIEW_SUCCESS        = 1,
  REVIEW_ERROR          = 2,
} review;

#endif



void StartReview(void);
uchar ReadReviewC(void);
