/*------------------------------------------------------------------------------
review_core.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports_common.h"
#include "review.h"
#include "review_core.h"



static uchar            mbBuff[100];
static uchar            cbRepeats, cbLimits;



void StartReview(void)
{
  memset(&mbBuff, 0, sizeof(mbBuff));
  cbRepeats = 0;
  cbLimits = 0;
}



static bool UseReview(void)
{
  return (bReviewRepeats > REVIEW_REPEATS_MIN) && (bReviewRepeats <= REVIEW_REPEATS_MAX);
}

static void SaveBuff(uchar  ibMin, uchar  ibMax)
{
  uchar i;
  for (i=ibMin; i<=ibMax; i++)
  {
    mbBuff[i] = InBuff(i);
  }
}

static bool TestBuff(uchar  ibMin, uchar  ibMax)
{
  uchar i;
  for (i=ibMin; i<=ibMax; i++)
  {
    if (mbBuff[i] != InBuff(i))
      return false;
  }

  return true;
}

static review ReadReview(uchar  ibMin, uchar  ibMax)
{
  if (!UseReview())
    return REVIEW_SUCCESS;
  else if (cbLimits == 0)
  {
    cbLimits++;
    SaveBuff(ibMin,ibMax);
    return REVIEW_REPEAT;
  }
  else
  {
    if (++cbLimits >= 10)
      return REVIEW_ERROR;
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
        return REVIEW_REPEAT;
      }
    }
  }
}


review ReadReviewC6(void)
{
  return ReadReview(0, 53);
}
