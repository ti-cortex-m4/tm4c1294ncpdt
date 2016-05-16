/*------------------------------------------------------------------------------
review_core.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports_common.h"
#include "review.h"
#include "review_core.h"



static uchar            mbBuff[100];
static uchar            cbSuccess,cbTotal;



void StartReview(void)
{
  memset(&mbBuff, 0, sizeof(mbBuff));
  cbSuccess = 0;
  cbTotal = 0;
}



static bool UseReview(void)
{
  return (bReviewRepeats >= 1) && (bReviewRepeats <= 5);
}

static void CopyBuff(uchar  ibMin, uchar  ibMax)
{
  uchar i;
  for (i=ibMin; i<=ibMax; i++)
  {
    mbBuff[i] = InBuff(i);
  }
}

static bool CheckBuff(uchar  ibMin, uchar  ibMax)
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
  else if (cbTotal == 0)
  {
    cbTotal++;
    CopyBuff(ibMin,ibMax);
    return REVIEW_REPEAT;
  }
  else
  {
    if (++cbTotal >= 10)
      return REVIEW_ERROR;
    else
    {
      if (CheckBuff(ibMin,ibMax))
      {
        if (++cbSuccess >= bReviewRepeats)
          return REVIEW_SUCCESS;
        else
          return REVIEW_REPEAT;
      }
      else
      {
        cbSuccess = 0;
        CopyBuff(ibMin,ibMax);
        return REVIEW_REPEAT;
      }
    }
  }
}


review ReadReviewC6(void)
{
  return ReadReview(0, 53);
}
