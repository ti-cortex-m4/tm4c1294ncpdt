/*------------------------------------------------------------------------------
review_warning.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "review.h"
#include "review_core.h"
#include "review_buff.h"
#include "review_warning.h"



static bool WarningInner(uint  wPrev, uint  wCurr)
{
  MonitorString(" "); MonitorIntDec(wPrev); MonitorString(" -> "); MonitorIntDec(wCurr);

  if ((wPrev != 0) && (wCurr == 0)) {
    Clear(); strcpy(szLo+3, "просечка ?"); DelayInf(); Clear();
    MonitorString(" warning: break ?");
    return true;
  }

  if ((wPrev != 0) && (wCurr == wPrev)) {
    Clear(); strcpy(szLo+4, "повтор ?"); DelayInf(); Clear();
    MonitorString(" warning: repeat ?");
    return true;
  }

  return false;
}

static bool Warning(uint  wPrev, uint  wCurr)
{
  if (WarningInner(wPrev, wCurr))
    bMaxRepeats = REVIEW_REPEATS_MAX;
    fIdRepeat = true;
    return true;
  }

  return false;
}

static bool WarningReviewBuffInner6(void)
{
  uchar i;
  for (i=0; i<4; i++) {
    if (Warning(PrevReviewBuff(5*4+i), CurrReviewBuff(0*4+i))) return true;
  }

  uchar j;
  for (j=0; j<5; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (Warning(CurrReviewBuff(j*4+i), CurrReviewBuff((j+1)*4+i))) return true;
    }
  }

  return false;
}

static bool WarningReviewBuffInner1(void)
{
  uchar i;
  for (i=0; i<4; i++) {
    if (Warning(PrevReviewBuff(i), CurrReviewBuff(i))) return true;
  }

  return false;
}

bool WarningReviewBuff(uchar  bSize)
{
  MonitorString("\n");
  switch(bSize) {
    case 0: return false;
    case 6: return WarningReviewBuffInner6();
    case 1: return WarningReviewBuffInner1();
    default: ASSERT(false); return false;
  }
}
