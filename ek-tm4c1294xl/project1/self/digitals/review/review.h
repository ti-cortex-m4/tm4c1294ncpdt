/*------------------------------------------------------------------------------
review.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW
#define __REVIEW

#define REVIEW_REPEAT_REGULAR_MIN   2
#define REVIEW_REPEAT_REGULAR_MAX   5
#define REVIEW_REPEAT_REGULAR_DEF   2

#define REVIEW_REPEAT_WARNING_MIN   2
#define REVIEW_REPEAT_WARNING_MAX   5
#define REVIEW_REPEAT_WARNING_DEF   4

#define REVIEW_REPEAT_TOTAL_MIN     10
#define REVIEW_REPEAT_TOTAL_MAX     50
#define REVIEW_REPEAT_TOTAL_DEF     20

#define REVIEW_WRN_PERCENT_MIN      100
#define REVIEW_WRN_PERCENT_MAX      50000
#define REVIEW_WRN_PERCENT_DEF      400

#define REVIEW_WRN_MAXIMUM_MIN      1
#define REVIEW_WRN_MAXIMUM_MAX      0xFFFF
#define REVIEW_WRN_MAXIMUM_DEF      0x7FFF



#define REVIEW_EVENTS_SIZE    16



extern bool                    fReviewFlag;
extern bool                    mfReviewCan[bCANALS];
extern bool                    fReviewReadId;
extern uchar                   bReviewRepeatRegular;
extern uchar                   bReviewRepeatWarning;
extern uchar                   bReviewRepeatTotal;
extern uint                    wReviewWrnPercent;
extern uint                    wReviewWrnMaximum;

extern uint                    mcwReviewEvents[REVIEW_EVENTS_SIZE];
extern uint                    mcwReviewWarnings[REVIEW_EVENTS_SIZE];

extern cache const             chReviewFlag;
extern cache const             chReviewCan;
extern cache const             chReviewReadId;
extern cache const             chReviewRepeatRegular;
extern cache const             chReviewRepeatWarning;
extern cache const             chReviewRepeatTotal;
extern cache const             chReviewWrnPercent;
extern cache const             chReviewWrnMaximum;



void InitReview(void);
void ResetReview(bool  fFull);

#endif
