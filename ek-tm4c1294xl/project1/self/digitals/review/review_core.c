/*------------------------------------------------------------------------------
review_core.c


------------------------------------------------------------------------------*/

#include "../../main.h"
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



static uchar ReadReview(void)
{
  if (cbTotal == 0)
  {
    if (bReviewRepeats == 0)
      return 0; // next profile
    else
    {
      cbTotal++;
      // copy
      return 1; // same profile
    }
  }
  else
  {
    if (++cbTotal >= 10)
    {
      return 2; // error
    }
    else
    {
      if (true) // is equal
      {
        if (++cbSuccess >= bReviewRepeats)
          return 0; // next profile
        else
          return 1; // same profile
      }
      else
      {
        // copy
        return 1; // same profile
      }
    }
  }
}


uchar   ReadReviewC(void)
{
 // copy
  return ReadReview();
}
