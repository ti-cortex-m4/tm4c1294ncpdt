/*------------------------------------------------------------------------------
review.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW
#define __REVIEW

#define REVIEW_REPEATS_MIN    1
#define REVIEW_REPEATS_MAX    5



extern bool                    fReviewReadId;
extern uchar                   bReviewRepeats;

extern cache const             chReviewReadId;
extern cache const             chReviewRepeats;



void InitReview(void);
void ResetReview(void);

#endif
