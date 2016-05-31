/*------------------------------------------------------------------------------
review_buff.h


------------------------------------------------------------------------------*/

extern  uint                    cwNextBuff;



uint PrevReviewBuff(uchar  i);
uint CurrReviewBuff(uchar  i);

void StartReviewBuff(void);
void RestartReviewBuff(void);

void NextReviewBuff(void);
void SaveReviewBuff(uchar  ibMin, uchar  ibMax);
bool TestReviewBuff(uchar  ibMin, uchar  ibMax);

void OutReviewBuff(void);
