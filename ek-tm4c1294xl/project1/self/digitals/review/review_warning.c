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



//                                         0123456789ABCDEF
static char const       szZero[]        = "      ноль ?    ",
                        szRepeat[]      = "    повтор ?    ",
                        szTop[]         = " абс. выброс ?  ",
                        szTrendTop[]    = " отн. выброс ?  ",
                        szTrendBottom[] = " отн. провал ?  ";



static review_wrn WarningCommonInner(uint  wPrev, uint  wCurr)
{
  MonitorString(" "); MonitorIntDec(wPrev); MonitorString(" -> "); MonitorIntDec(wCurr);

  if ((cwNextBuff > 1) && (wPrev != 0) && (wCurr == 0)) {
    ShowLo(szZero); DelayInf(); Clear();
    MonitorString(" WARNING: value 0");
    return REVIEW_WRN_ZERO;
  }

//  if ((cwNextBuff > 1) && (wPrev != 0) && (wCurr == wPrev)) {
//    ShowLo(szRepeat); DelayInf(); Clear();
//    MonitorString(" WARNING: repeat ?");
//    return REVIEW_WRN_REPEAT;
//  }

  if (wCurr > wReviewWrnTop) {
    ShowLo(szTop); DelayInf(); Clear();
    MonitorString(" WARNING: value > "); MonitorIntDec(wReviewWrnTop);
    return REVIEW_WRN_TOP;
  }

  ulong dwCurrMax = wPrev*(100 + bReviewWrnTrend) / 100;
  ulong dwCurrMin = wPrev*(100 - bReviewWrnTrend) / 100;

  if ((cwNextBuff > 1) && (wCurr > dwCurrMax)) {
    ShowLo(szTrendTop); DelayInf(); Clear();
    MonitorString(" WARNING: value > "); MonitorLongDec(dwCurrMax); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
    return REVIEW_WRN_TREND_TOP;
  }

  if ((cwNextBuff > 1) && (wCurr < dwCurrMin)) {
    ShowLo(szTrendBottom); DelayInf(); Clear();
    MonitorString(" WARNING: value < "); MonitorLongDec(dwCurrMin); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
    return REVIEW_WRN_TREND_BOTTOM;
  }

  return REVIEW_WRN_OK;
}

static review_wrn WarningRepeatsInner(uint  wPrev, uint  wCurr)
{
  MonitorString(" "); MonitorIntDec(wPrev); MonitorString(" => "); MonitorIntDec(wCurr);

  if ((cwNextBuff > 1) && (wPrev != 0) && (wCurr == wPrev)) {
    ShowLo(szRepeat); DelayInf(); Clear();
    MonitorString(" WARNING: repeat ?");
    return REVIEW_WRN_REPEAT;
  }

  return REVIEW_WRN_OK;
}

static bool WarningCommon(uint  wPrev, uint  wCurr)
{
  review_wrn rw = WarningCommonInner(wPrev, wCurr);
  if (rw != REVIEW_WRN_OK) {
    bMaxRepeats = bReviewBorders;
    fIdRepeat = true;

    mcwReviewWarnings[rw]++;
    return true;
  }

  return false;
}

static bool WarningRepeats(uint  wPrev, uint  wCurr)
{
  review_wrn rw = WarningRepeatsInner(wPrev, wCurr);
  if (rw != REVIEW_WRN_OK) {
    bMaxRepeats = bReviewBorders;
    fIdRepeat = true;

    mcwReviewWarnings[rw]++;
    return true;
  }

  return false;
}

static bool WarningReviewBuff6(void)
{
  uchar i;
  for (i=0; i<4; i++) {
    if (WarningCommon(PrevReviewInt(5*4+i), CurrReviewInt(0*4+i))) return true;
  }

  MonitorString("\n -");

  uchar j;
  for (j=0; j<6-1; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (WarningCommon(CurrReviewInt(j*4+i), CurrReviewInt((j+1)*4+i))) return true;
    }
  }

  MonitorString("\n -");

  for (j=0; j<6; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (WarningRepeats(PrevReviewInt(j*4+i), CurrReviewInt(j*4+i))) return true;
    }
  }

  return false;
}

static bool WarningReviewBuff1(void)
{
  MonitorString("\n");

  uchar i;
  for (i=0; i<4; i++) {
    if (WarningCommon(PrevReviewInt(i), CurrReviewInt(i))) return true;
  }

  for (i=0; i<4; i++) {
    if (WarningRepeats(PrevReviewInt(i), CurrReviewInt(i))) return true;
  }

  return false;
}

bool WarningReviewBuff(uchar  bSize)
{
  switch(bSize) {
    case 0: return false;
    case 6: return WarningReviewBuff6();
    case 1: return WarningReviewBuff1();
    default: ASSERT(false); return false;
  }
}
