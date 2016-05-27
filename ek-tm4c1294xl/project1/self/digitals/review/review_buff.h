/*------------------------------------------------------------------------------
review_buff.h


------------------------------------------------------------------------------*/

uint Prev(uchar  i);
uint Curr(uchar  i);

void StartReviewBuff(void);
void RestartReviewBuff(void);

void NextReviewBuff(void);
void SaveReviewBuff(uchar  ibMin, uchar  ibMax);
bool TestReviewBuff(uchar  ibMin, uchar  ibMax);

void OutReviewBuff(void);
