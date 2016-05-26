/*------------------------------------------------------------------------------
review_core.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "../../serial/monitor.h"
#include "review.h"
#include "review_buff.h"
#include "review_core.h"



static uchar            cbRepeats, cbMargins;

uchar                   bMaxRepeats;
bool                    fIdRepeat;



void StartReview(void)
{
  StartReviewBuff();
}

void RestartReview(void)
{
  RestartReviewBuff();

  cbRepeats = 0;
  cbMargins = 0;

  bMaxRepeats = bReviewRepeats;
  fIdRepeat = false;
}



static bool UseReview(void)
{
  return (fReviewFlag == true);
}

static void Show(void)
{
  sprintf(szHi+10, "%2u", cbMargins);
}



static review ReadReviewInner(uchar  ibMin, uchar  ibMax)
{
  if (!UseReview()) {
    return REVIEW_SUCCESS;
  } else if (cbMargins == 0) {
    cbMargins++;
    Show();

    cbRepeats++;
    SaveReviewBuff(ibMin,ibMax);

    if (SpecReviewBuff()) {
      Clear(); strcpy(szLo+3, "проверка !!"); DelayInf(); Clear();
    }
    return REVIEW_REPEAT;
  } else {
    cbMargins++;
    Show();

    if (cbMargins >= bReviewMargins) {
      Clear(); strcpy(szLo+0, "ошибка проверки"); DelayMsg(); Clear();
      return REVIEW_ERROR;
    } else {
      if (TestReviewBuff(ibMin,ibMax)) {
        if (++cbRepeats >= bMaxRepeats) {
          SwitchReviewBuff();
          return REVIEW_SUCCESS;
        } else {
          return REVIEW_REPEAT;
        }
      } else {
        cbRepeats = 0;
        SaveReviewBuff(ibMin,ibMax);

        if (SpecReviewBuff()) {
          Clear(); strcpy(szLo+3, "проверка !!"); DelayInf(); Clear();
        } else {
          Clear(); strcpy(szLo+3, "проверка !"); DelayInf(); Clear();
        }
        return REVIEW_REPEAT;
      }
    }
  }
}

static review ReadReview(uchar  ibMin, uchar  ibMax)
{
  review rv = ReadReviewInner(ibMin, ibMax);

  if ((rv == REVIEW_REPEAT) && (fIdRepeat == true)) {
    rv = REVIEW_ID_REPEAT;
    MonitorString("\n REVIEW_ID_REPEAT");
  }

  if (rv == REVIEW_REPEAT) {
    MonitorString("\n REVIEW_REPEAT");
  }

  return rv;
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
