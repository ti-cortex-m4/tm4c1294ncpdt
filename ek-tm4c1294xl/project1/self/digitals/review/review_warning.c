/*------------------------------------------------------------------------------
review_warning.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../serial/ports_common.h"
//#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "review.h"
#include "review_core.h"
#include "review_buff.h"
#include "review_warning.h"



static bool Warn(uint  wPrev, uint  wCurr)
{
  MonitorString("\n "); MonitorIntDec(wPrev); MonitorString(" -> "); MonitorIntDec(wCurr);

  if ((wPrev != 0) && (wCurr == 0)) {
    Clear(); strcpy(szLo+3, "просечка ?"); DelayInf(); Clear();
    MonitorString(" warnig: break ?");

    bMaxRepeats = REVIEW_REPEATS_MAX;
    fIdRepeat = true;
    return true;
  }

  if ((wPrev != 0) && (wCurr == wPrev)) {
    Clear(); strcpy(szLo+4, "повтор ?"); DelayInf(); Clear();
    MonitorString(" warnig: repeat ?");

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
    if (Warn(Prev(5*4+i),Curr(0*4+i))) return true;
  }

  uchar j;
  for (j=0; j<5; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (Warn(Curr(j*4+i),Curr((j+1)*4+i))) return true;
    }
  }

  return false;
}

static bool WarnReviewBuffInner1(void)
{
  uchar i;
  for (i=0; i<4; i++) {
    if (Warn(Prev(i),Curr(i))) return true;
  }

  return false;
}

bool WarnReviewBuff(uchar  bSize)
{
  switch(bSize) {
    case 0: return false;
    case 6: return WarnReviewBuffInner6();
    case 1: return WarnReviewBuffInner1();
    default: ASSERT(false); return false;
  }
}
