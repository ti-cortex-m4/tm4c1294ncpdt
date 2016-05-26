/*------------------------------------------------------------------------------
review_core.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW_CORE
#define __REVIEW_CORE

typedef enum
{
  REVIEW_REPEAT         = 0,
  REVIEW_ID_REPEAT      = 1,
  REVIEW_SUCCESS        = 2,
  REVIEW_ERROR          = 3,
} review;



extern  uchar                   bMaxRepeats;



void StartReview(void);
void RestartReview(void);

review ReadReviewC1(void);
review ReadReviewC1_Shutdown(void);
review ReadReviewC6(void);

#endif
