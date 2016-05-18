/*------------------------------------------------------------------------------
review.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW
#define __REVIEW

#define REVIEW_REPEATS_MIN    1
#define REVIEW_REPEATS_MAX    5

#define REVIEW_MARGINS_MIN    10
#define REVIEW_MARGINS_MAX    25



extern bool                    fReviewReadId;
extern uchar                   bReviewRepeats;
extern uchar                   bReviewMargins;

extern cache const             chReviewReadId;
extern cache const             chReviewRepeats;
extern cache const             chReviewMargins;



void InitReview(void);
void ResetReview(void);

#endif
