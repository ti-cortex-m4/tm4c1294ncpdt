/*------------------------------------------------------------------------------
review_buff.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports_common.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "review.h"
#include "review_core.h"
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



void StartReviewBuff(void)
{
  MonitorString("\n start review buff");

  memset(&mmbBuff, 0, sizeof(mmbBuff));
  ibBuff = 0;
}

void RestartReviewBuff(void)
{
  MonitorString("\n restart review buff");

  memset(&mmbBuff[CurrBuffIdx()], 0, REVIEW_BUFF_SIZE);
}



void NextReviewBuff(void)
{
  MonitorString("\n next review buff");

  ibBuff = ++ibBuff % REVIEW_BUFF_COUNT;
  memset(&mmbBuff[CurrBuffIdx()], 0, REVIEW_BUFF_SIZE);
}



static uint Prev(uchar  i)
{
  return mmbBuff[PrevBuffIdx()][4+i*2] + mmbBuff[PrevBuffIdx()][4+i*2+1]*0x100;
}

static uint Curr(uchar  i)
{
  return mmbBuff[CurrBuffIdx()][4+i*2] + mmbBuff[CurrBuffIdx()][4+i*2+1]*0x100;
}

static bool Warn(uint  wPrev, uint  wCurr)
{
  MonitorString("\n "); MonitorIntDec(wPrev); MonitorString(" -> "); MonitorIntDec(wCurr);

  if ((wPrev != 0) && (wCurr == 0)) {
    Clear(); strcpy(szLo+3, "просечка ?"); DelayInf(); Clear();
    MonitorString("\n warnig: break ?");

    bMaxRepeats = REVIEW_REPEATS_MAX;
    fIdRepeat = true;
    return true;
  }

  if ((wPrev != 0) && (wCurr == wPrev)) {
    Clear(); strcpy(szLo+4, "повтор ?"); DelayInf(); Clear();
    MonitorString("\n warnig: repeat ?");

    bMaxRepeats = REVIEW_REPEATS_MAX;
    fIdRepeat = true;
    return true;
  }

  return false;
}

static bool WarnReviewBuffInner6(void)
{
  uchar i;
  for (i=0; i<4; i++) {
    uint wPrev = Prev(5*6+i);
    uint wCurr = Curr(0*6+i);
    if (Warn(wPrev,wCurr) == true) return true;
  }

  uchar j;
  for (j=0; j<5; j++) {
    uchar i;
    for (i=0; i<4; i++) {
      uint wPrev = Curr(j*6+i);
      uint wCurr = Curr((j+1)*6+i);
      if (Warn(wPrev,wCurr) == true) return true;
    }
  }

  return false;
}

static bool WarnReviewBuffInner1(void)
{
  uchar i;
  for (i=0; i<4; i++) {
    uint wPrev = mmbBuff[PrevBuffIdx()][4+i*2] + mmbBuff[PrevBuffIdx()][4+i*2+1]*0x100;
    uint wCurr = mmbBuff[CurrBuffIdx()][4+i*2] + mmbBuff[CurrBuffIdx()][4+i*2+1]*0x100;
    MonitorString("\n "); MonitorIntDec(wPrev); MonitorString(" -> "); MonitorIntDec(wCurr);

    if ((wPrev != 0) && (wCurr == 0)) {
      Clear(); strcpy(szLo+3, "просечка ?"); DelayInf(); Clear();
      MonitorString("\n warnig: break ?");

      bMaxRepeats = REVIEW_REPEATS_MAX;
      fIdRepeat = true;
      return true;
    }

    if ((wPrev != 0) && (wCurr == wPrev)) {
      Clear(); strcpy(szLo+4, "повтор ?"); DelayInf(); Clear();
      MonitorString("\n warnig: repeat ?");

      bMaxRepeats = REVIEW_REPEATS_MAX;
      fIdRepeat = true;
      return true;
    }
  }

  return false;
}

bool WarnReviewBuff(uchar  bSize)
{
  switch(bSize) {
    case 0: return false;
    case 6: return false;
    case 1: return WarnReviewBuffInner1();
    default: ASSERT(false); return false;
  }
}



void SaveReviewBuff(uchar  ibMin, uchar  ibMax)
{
  MonitorString("\n save review buff");
  memset(&mmbBuff[CurrBuffIdx()], 0, REVIEW_BUFF_SIZE);

  uchar i;
  for (i=ibMin; i<=ibMax; i++)
  {
    ASSERT(i < REVIEW_BUFF_SIZE);
    mmbBuff[CurrBuffIdx()][i] = InBuff(i);
  }
}

bool TestReviewBuff(uchar  ibMin, uchar  ibMax)
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
