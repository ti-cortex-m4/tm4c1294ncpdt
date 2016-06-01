/*------------------------------------------------------------------------------
review_core.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "../../serial/monitor.h"
#include "review.h"
#include "review_buff.h"
#include "review_wrn.h"
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



static review_code ReadReviewInner(uchar  ibMin, uchar  ibMax, uchar  bSize)
{
  if (!UseReview()) {
    return REVIEW_SUCCESS;
  } else if (cbMargins == 0) {
    cbMargins++;
    Show();

    cbRepeats++;
    SaveReviewBuff(ibMin,ibMax);

    WrnReviewBuff(bSize);
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
          NextReviewBuff();
          return REVIEW_SUCCESS;
        } else {
          return REVIEW_REPEAT;
        }
      } else {
        cbRepeats = 0;
        SaveReviewBuff(ibMin,ibMax);

        if (!WrnReviewBuff(bSize)) {
          Clear(); strcpy(szLo+3, "проверка !"); DelayInf(); Clear();
        }
        return REVIEW_REPEAT;
      }
    }
  }
}

static review_code ReadReview(uchar  ibMin, uchar  ibMax, uchar  bSize)
{
  review_code rc = ReadReviewInner(ibMin, ibMax, bSize);

  if ((rc == REVIEW_REPEAT) && (fIdRepeat == true)) {
    rc = REVIEW_ID_REPEAT;
    MonitorString("\n REVIEW_ID_REPEAT");
  }

  if (rc == REVIEW_REPEAT) {
    MonitorString("\n REVIEW_REPEAT");
  }

  mcwReviewEvent[rc]++;

  return rc;
}



review_code ReadReviewC1(void)
{
  return ReadReview(0, 13, 1);
}

review_code ReadReviewC1_Shutdown(void)
{
  return ReadReview(0, 5, 0);
}

review_code ReadReviewC6(void)
{
  return ReadReview(0, 53, 6);
}
