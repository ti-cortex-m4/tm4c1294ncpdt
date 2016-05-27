/*------------------------------------------------------------------------------
review_buff.h


------------------------------------------------------------------------------*/

uint PrevReview(uchar  i);
uint CurrReview(uchar  i);

void StartReviewBuff(void);
void RestartReviewBuff(void);

void NextReviewBuff(void);
void SaveReviewBuff(uchar  ibMin, uchar  ibMax);
bool TestReviewBuff(uchar  ibMin, uchar  ibMax);

void OutReviewBuff(void);
