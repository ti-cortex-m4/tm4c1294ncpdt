/*------------------------------------------------------------------------------
review.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW
#define __REVIEW

#define REVIEW_REPEATS_MIN    1
#define REVIEW_REPEATS_MAX    5
#define REVIEW_REPEATS_DEF    1

#define REVIEW_BORDERS_MIN    1
#define REVIEW_BORDERS_MAX    5
#define REVIEW_BORDERS_DEF    5

#define REVIEW_MARGINS_MIN    10
#define REVIEW_MARGINS_MAX    50
#define REVIEW_MARGINS_DEF    20

#define REVIEW_WRN_TREND_MIN  5
#define REVIEW_WRN_TREND_MAX  95
#define REVIEW_WRN_TREND_DEF  50

#define REVIEW_WRN_TOP_MIN    100
#define REVIEW_WRN_TOP_MAX    0xFFFF
#define REVIEW_WRN_TOP_DEF    30000



extern bool                    fReviewFlag;
extern bool                    fReviewReadId;
extern uchar                   bReviewRepeats;
extern uchar                   bReviewBorders;
extern uchar                   bReviewMargins;
extern uchar                   bReviewWrnTrend;
extern uint                    wReviewWrnTop;

extern uint                    mcwReviewEvent[16];
extern uint                    mcwReviewWarning[16];

extern cache const             chReviewFlag;
extern cache const             chReviewReadId;
extern cache const             chReviewRepeats;
extern cache const             chReviewBorders;
extern cache const             chReviewMargins;
extern cache const             chReviewWrnTrend;
extern cache const             chReviewWrnTop;



void InitReview(void);
void ResetReview(bool  fFull);

#endif
