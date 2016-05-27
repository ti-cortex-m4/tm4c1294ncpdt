/*------------------------------------------------------------------------------
review_buff.h


------------------------------------------------------------------------------*/

void StartReviewBuff(void);
void RestartReviewBuff(void);

void SwitchReviewBuff(void);
bool WarnReviewBuff(uchar  bCount);
void SaveReviewBuff(uchar  ibMin, uchar  ibMax);
bool TestReviewBuff(uchar  ibMin, uchar  ibMax);

void OutReviewBuff(void);
