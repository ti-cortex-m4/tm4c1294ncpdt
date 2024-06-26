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
} review_code;



extern  uchar                   bReviewRepeatMax;
extern  bool                    fReviewIdRepeat;



void StartReview(void);
void RestartReview(void);

review_code ReadReviewC1(void);
review_code ReadReviewC1_Shutdown(void);
review_code ReadReviewC6(void);

#endif
