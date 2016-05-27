/*------------------------------------------------------------------------------
review.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW
#define __REVIEW

#define REVIEW_REPEATS_MIN    1
#define REVIEW_REPEATS_MAX    5

#define REVIEW_MARGINS_MIN    10
#define REVIEW_MARGINS_MAX    50



extern bool                    fReviewFlag;
extern bool                    fReviewReadId;
extern uchar                   bReviewRepeats;
extern uchar                   bReviewMargins;
extern uchar                   bReviewWrnPercent;
extern uint                    wReviewWrnTop;

extern cache const             chReviewFlag;
extern cache const             chReviewReadId;
extern cache const             chReviewRepeats;
extern cache const             chReviewMargins;
extern cache const             chReviewWrnPercent;
extern cache const             chReviewWrnTop;



void InitReview(void);
void ResetReview(bool  fFull);

#endif
