/*------------------------------------------------------------------------------
review_buff.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../display/display.h"
//#include "../../time/delay.h"
//#include "../../serial/ports_common.h"
//#include "../../serial/ports.h"
//#include "review.h"
#include "review_buff.h"



#define REVIEW_BUFF_COUNT    2
#define REVIEW_BUFF_SIZE     100


static uchar            mmbBuff[REVIEW_BUFF_COUNT][REVIEW_BUFF_SIZE];
static uchar            ibBuff;



static uchar CurrBuffIdx(void)
{
  return (ibBuff == 0) ? 0 : 1;
}

static uchar PrevBuffIdx(void)
{
  return (ibBuff == 0) ? 1 : 0;
}

static voidNextBuffIdx(void)
{
  ibBuff = ++ibBuff % REVIEW_BUFF_COUNT;
}



void StartReviewBuff(void)
{
  memset(&mmbBuff, 0, sizeof(mmbBuff));
  ibBuff = 0;
}



{
  memset(&mmbBuff[CurrBuffIdx()], 0, REVIEW_BUFF_SIZE);

  uchar i;
  for (i=ibMin; i<=ibMax; i++)
  {
    ASSERT(i < REVIEW_BUFF_SIZE);
    mmbBuff[CurrBuffIdx()][i] = InBuff(i);
  }
}

{
  uchar i;
  for (i=ibMin; i<=ibMax; i++)
  {
    ASSERT(i < REVIEW_BUFF_SIZE);
    if (mmbBuff[CurrBuffIdx()][i] != InBuff(i))
      return false;
  }

  return true;
}



void OutReviewBuff(void)
{
  InitPushCRC();
  uint wSize = 0;

  wSize += PushIntBig(REVIEW_BUFF_SIZE);
  wSize += PushChar(REVIEW_BUFF_COUNT);
  wSize += PushChar(ibBuff);
  wSize += PushChar(CurrBuffIdx());
  wSize += PushChar(PrevBuffIdx());
  wSize += Push(&mmbBuff, sizeof(mmbBuff));

  Output(wSize);
}
