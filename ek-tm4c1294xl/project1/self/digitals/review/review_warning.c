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



static review_wrn WarningInnerA(uint  wPrev, uint  wCurr)
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

static review_wrn WarningInnerB(uint  wPrev, uint  wCurr)
{
  MonitorString(" "); MonitorIntDec(wPrev); MonitorString(" => "); MonitorIntDec(wCurr);

//  if ((cwNextBuff > 1) && (wPrev != 0) && (wCurr == 0)) {
//    ShowLo(szZero); DelayInf(); Clear();
//    MonitorString(" WARNING: value 0");
//    return REVIEW_WRN_ZERO;
//  }

  if ((cwNextBuff > 1) && (wPrev != 0) && (wCurr == wPrev)) {
    ShowLo(szRepeat); DelayInf(); Clear();
    MonitorString(" WARNING: repeat ?");
    return REVIEW_WRN_REPEAT;
  }

//  if (wCurr > wReviewWrnTop) {
//    ShowLo(szTop); DelayInf(); Clear();
//    MonitorString(" WARNING: value > "); MonitorIntDec(wReviewWrnTop);
//    return REVIEW_WRN_TOP;
//  }
//
//  ulong dwCurrMax = wPrev*(100 + bReviewWrnTrend) / 100;
//  ulong dwCurrMin = wPrev*(100 - bReviewWrnTrend) / 100;
//
//  if ((cwNextBuff > 1) && (wCurr > dwCurrMax)) {
//    ShowLo(szTrendTop); DelayInf(); Clear();
//    MonitorString(" WARNING: value > "); MonitorLongDec(dwCurrMax); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
//    return REVIEW_WRN_TREND_TOP;
//  }
//
//  if ((cwNextBuff > 1) && (wCurr < dwCurrMin)) {
//    ShowLo(szTrendBottom); DelayInf(); Clear();
//    MonitorString(" WARNING: value < "); MonitorLongDec(dwCurrMin); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
//    return REVIEW_WRN_TREND_BOTTOM;
//  }

  return REVIEW_WRN_OK;
}

static bool WarningA(uint  wPrev, uint  wCurr)
{
  review_wrn rw = WarningInnerA(wPrev, wCurr);
  if (rw != REVIEW_WRN_OK) {
    bMaxRepeats = bReviewBorders;
    fIdRepeat = true;

    mcwReviewWarnings[rw]++;
    return true;
  }

  return false;
}

static bool WarningB(uint  wPrev, uint  wCurr)
{
  review_wrn rw = WarningInnerB(wPrev, wCurr);
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
    if (WarningA(PrevReviewBuff(5*4+i), CurrReviewBuff(0*4+i))) return true;
  }

  MonitorString("\n -");

  uchar j;
  for (j=0; j<6-1; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (WarningA(CurrReviewBuff(j*4+i), CurrReviewBuff((j+1)*4+i))) return true;
    }
  }

  MonitorString("\n -");

  for (j=0; j<6; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (WarningB(PrevReviewBuff(j*4+i), CurrReviewBuff(j*4+i))) return true;
    }
  }

  return false;
}

static bool WarningReviewBuff1(void)
{
  MonitorString("\n");

  uchar i;
  for (i=0; i<4; i++) {
    if (WarningA(PrevReviewBuff(i), CurrReviewBuff(i))) return true;
  }

  for (i=0; i<4; i++) {
    if (WarningB(PrevReviewBuff(i), CurrReviewBuff(i))) return true;
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
