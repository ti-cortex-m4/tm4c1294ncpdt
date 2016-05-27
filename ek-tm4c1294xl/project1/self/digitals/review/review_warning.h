/*------------------------------------------------------------------------------
review_buff.h


------------------------------------------------------------------------------*/

void StartReviewBuff(void);
void RestartReviewBuff(void);

void NextReviewBuff(void);
bool WarnReviewBuff(uchar  bSize);
void SaveReviewBuff(uchar  ibMin, uchar  ibMax);
bool TestReviewBuff(uchar  ibMin, uchar  ibMax);

void OutReviewBuff(void);
