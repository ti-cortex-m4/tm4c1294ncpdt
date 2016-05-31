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

  if ((cwNextBuff > 1) && (wPrev != 0) && (wCurr == 0)) {
    Clear(); strcpy(szLo+3, "просечка ?"); DelayInf(); Clear();
    MonitorString(" warning: value = 0");
    return true;
  }

  if ((cwNextBuff > 1) && (wPrev != 0) && (wCurr == wPrev)) {
    Clear(); strcpy(szLo+4, "повтор ?"); DelayInf(); Clear();
    MonitorString(" warning: repeat ?");
    return true;
  }

  if (wCurr > wReviewWrnTop) {
    Clear(); strcpy(szLo+4, "выброс ?"); DelayInf(); Clear();
    MonitorString(" warning: value > "); MonitorIntDec(wReviewWrnTop);
    return true;
  }

  ulong dwMax = wPrev*(100 + bReviewWrnTrend) / 100;
  ulong dwMin = wPrev*(100 - bReviewWrnTrend) / 100;

  if ((cwNextBuff > 1) && (wCurr > dwMax)) {
    Clear(); strcpy(szLo+4, "пик ?"); DelayInf(); Clear();
    MonitorString(" warning: value > "); MonitorLongDec(dwMax); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
    return true;
  }

  if ((cwNextBuff > 1) && (wCurr < dwMin)) {
    Clear(); strcpy(szLo+4, "провал ?"); DelayInf(); Clear();
    MonitorString(" warning: value < "); MonitorLongDec(dwMin); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
    return true;
  }

  return false;
}

static bool Warning(uint  wPrev, uint  wCurr)
{
  if (WarningInner(wPrev, wCurr)) {
    bMaxRepeats = REVIEW_REPEATS_MAX;
    fIdRepeat = true;
    return true;
  }

  return false;
}

static bool WarningReviewBuff6(void)
{
/*
  MonitorString("\n");

  uchar i;
  for (i=0; i<4; i++) {
    if (Warning(PrevReviewBuff(5*4+i), CurrReviewBuff(0*4+i))) return true;
  }

  MonitorString("\n");

  uchar j;
  for (j=0; j<6-1; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (Warning(CurrReviewBuff(j*4+i), CurrReviewBuff((j+1)*4+i))) return true;
    }
  }
*/
  MonitorString("\n");

  uchar j;
  for (j=0; j<6; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (Warning(PrevReviewBuff(j*4+i), CurrReviewBuff(j*4+i))) return true;
    }
  }

  return false;
}

static bool WarningReviewBuff1(void)
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
    case 6: return WarningReviewBuff6();
    case 1: return WarningReviewBuff1();
    default: ASSERT(false); return false;
  }
}
