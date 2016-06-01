/*------------------------------------------------------------------------------
review_wrn.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "review.h"
#include "review_core.h"
#include "review_buff.h"
#include "review_wrn.h"



static review_wrn WrnInner(uint  wPrev, uint  wCurr)
{
  MonitorString(" "); MonitorIntDec(wPrev); MonitorString(" -> "); MonitorIntDec(wCurr);

  if ((cwNextBuff > 1) && (wPrev != 0) && (wCurr == 0)) {
    Clear(); strcpy(szLo+3, "просечка ?"); DelayInf(); Clear();
    MonitorString(" warning: zero value");
    return REVIEW_WRN_ZERO;
  }

  if ((cwNextBuff > 1) && (wPrev != 0) && (wCurr == wPrev)) {
    Clear(); strcpy(szLo+4, "повтор ?"); DelayInf(); Clear();
    MonitorString(" warning: repeat ?");
    return REVIEW_WRN_REPEAT;
  }

  if (wCurr > wReviewWrnTop) {
    Clear(); strcpy(szLo+4, "выброс ?"); DelayInf(); Clear();
    MonitorString(" warning: value > "); MonitorIntDec(wReviewWrnTop);
    return REVIEW_WRN_TOP;
  }

  ulong dwCurrMax = wPrev*(100 + bReviewWrnTrend) / 100;
  ulong dwCurrMin = wPrev*(100 - bReviewWrnTrend) / 100;

  if ((cwNextBuff > 1) && (wCurr > dwCurrMax)) {
    Clear(); strcpy(szLo+4, "пик ?"); DelayInf(); Clear();
    MonitorString(" warning: value > "); MonitorLongDec(dwCurrMax); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
    return REVIEW_WRN_TREND_TOP;
  }

  if ((cwNextBuff > 1) && (wCurr < dwCurrMin)) {
    Clear(); strcpy(szLo+4, "провал ?"); DelayInf(); Clear();
    MonitorString(" warning: value < "); MonitorLongDec(dwCurrMin); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
    return REVIEW_WRN_TREND_BOTTOM;
  }

  return REVIEW_WRN_OK;
}

static bool Wrn(uint  wPrev, uint  wCurr)
{
  review_wrn rw = WrnInner(wPrev, wCurr);

  if (rw != REVIEW_WRN_OK) {
    bMaxRepeats = bReviewBorders;
    fIdRepeat = true;

    mcwReviewWrn[rw]++;
    return true;
  }

  return false;
}

static bool WrnReviewBuff6(void)
{
  uchar i;
  for (i=0; i<4; i++) {
    if (Wrn(PrevReviewBuff(5*4+i), CurrReviewBuff(0*4+i))) return true;
  }

  MonitorString("\n -");

  uchar j;
  for (j=0; j<6-1; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (Wrn(CurrReviewBuff(j*4+i), CurrReviewBuff((j+1)*4+i))) return true;
    }
  }

  MonitorString("\n -");

  for (j=0; j<6; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (Wrn(PrevReviewBuff(j*4+i), CurrReviewBuff(j*4+i))) return true;
    }
  }

  return false;
}

static bool WrnReviewBuff1(void)
{
  uchar i;
  for (i=0; i<4; i++) {
    if (Wrn(PrevReviewBuff(i), CurrReviewBuff(i))) return true;
  }

  return false;
}

bool WrnReviewBuff(uchar  bSize)
{
  MonitorString("\n");
  switch(bSize) {
    case 0: return false;
    case 6: return WrnReviewBuff6();
    case 1: return WrnReviewBuff1();
    default: ASSERT(false); return false;
  }
}
