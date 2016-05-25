/*------------------------------------------------------------------------------
review_core.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "../../serial/ports_common.h"
#include "../../serial/ports.h"
#include "review.h"
#include "review_core.h"



#define REVIEW_BUFF_SIZE     100
#define REVIEW_BUFF_COUNT    2


static uchar            mmbBuff[REVIEW_BUFF_SIZE][REVIEW_BUFF_COUNT];
static uchar            ibBuff;
static uchar            cbRepeats, cbMargins;



static uchar CurrBuffIdx(void)
{
  return (ibBuff == 0) ? 0 : 1;
}

static uchar PrevBuffIdx(void)
{
  return (ibBuff == 0) ? 1 : 0;
}



void StartReview(void)
{
  memset(&mmbBuff, 0, sizeof(mmbBuff));
  ibBuff = 0;

  cbRepeats = 0;
  cbMargins = 0;
}



static bool UseReview(void)
{
  return (bReviewRepeats > REVIEW_REPEATS_MIN) && (bReviewRepeats <= REVIEW_REPEATS_MAX);
}

static void Show(void)
{
  sprintf(szHi+10, "%2u", cbMargins);
}

static void SaveBuff(uchar  ibMin, uchar  ibMax)
{
  memset(&mbBuff, 0, sizeof(mbBuff));

  uchar i;
  for (i=ibMin; i<=ibMax; i++)
  {
    ASSERT(i < REVIEW_BUFF_SIZE);
    mbBuff[i] = InBuff(i);
  }
}

static bool TestBuff(uchar  ibMin, uchar  ibMax)
{
  uchar i;
  for (i=ibMin; i<=ibMax; i++)
  {
    ASSERT(i < REVIEW_BUFF_SIZE);
    if (mbBuff[i] != InBuff(i))
      return false;
  }

  return true;
}


static review ReadReview(uchar  ibMin, uchar  ibMax)
{
  if (!UseReview())
    return REVIEW_SUCCESS;
  else if (cbMargins == 0)
  {
    cbMargins++;
    Show();

    cbRepeats++;
    SaveBuff(ibMin,ibMax);
    return REVIEW_REPEAT;
  }
  else
  {
    cbMargins++;
    Show();

    if (cbMargins >= bReviewMargins)
    {
      Clear(); strcpy(szLo+0, "ошибка проверки"); DelayMsg(); Clear();
      return REVIEW_ERROR;
    }
    else
    {
      if (TestBuff(ibMin,ibMax))
      {
        if (++cbRepeats >= bReviewRepeats)
          return REVIEW_SUCCESS;
        else
          return REVIEW_REPEAT;
      }
      else
      {
        cbRepeats = 0;
        SaveBuff(ibMin,ibMax);
        Clear(); strcpy(szLo+3, "проверка !"); DelayInf(); Clear();
        return REVIEW_REPEAT;
      }
    }
  }
}



review ReadReviewC1(void)
{
  return ReadReview(0, 13);
}

review ReadReviewC1_Shutdown(void)
{
  return ReadReview(0, 5);
}

review ReadReviewC6(void)
{
  return ReadReview(0, 53);
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
