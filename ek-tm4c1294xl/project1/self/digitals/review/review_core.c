/*------------------------------------------------------------------------------
review_core.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "review.h"
#include "review_buff.h"
#include "review_core.h"



static uchar            cbRepeats, cbMargins;



void StartReview(void)
{
  StartReviewBuff();

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



static review ReadReview(uchar  ibMin, uchar  ibMax)
{
  if (!UseReview()) {
    return REVIEW_SUCCESS;
  } else if (cbMargins == 0) {
    cbMargins++;
    Show();

    cbRepeats++;
    SaveReviewBuff(ibMin,ibMax);

    if (SpecReviewBuff()) {
      Clear(); strcpy(szLo+3, "проверка *"); DelayInf(); Clear();
      return REVIEW_ID_REPEAT;
    } else {
      return REVIEW_REPEAT;
    }
  } else {
    cbMargins++;
    Show();

    if (cbMargins >= bReviewMargins) {
      Clear(); strcpy(szLo+0, "ошибка проверки"); DelayMsg(); Clear();
      return REVIEW_ERROR;
    } else {
      if (TestReviewBuff(ibMin,ibMax)) {
        if (++cbRepeats >= bReviewRepeats) {
          SwitchReviewBuff();
          return REVIEW_SUCCESS;
        } else {
          return REVIEW_REPEAT;
        }
      } else {
        cbRepeats = 0;
        SaveReviewBuff(ibMin,ibMax);

        if (SpecReviewBuff()) {
          Clear(); strcpy(szLo+3, "проверка *"); DelayInf(); Clear();
          return REVIEW_ID_REPEAT;
        } else {
          Clear(); strcpy(szLo+3, "проверка !"); DelayInf(); Clear();
          return REVIEW_REPEAT;
        }
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
