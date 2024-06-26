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
#include "review_can.h"
#include "review_warning.h"



//                                           0123456789ABCDEF
static char const       szZero[]          = "  просечка ?    ",
                        szRepeat[]        = "   повтор ?     ",
                        szTop[]           = "   выброс ?     ",
                        szPercentTop[]    = "   рост %u%%     ",
                        szPercentBottom[] = "   спад %u%%     ";



static void Show1(char const  *sz, uchar  c)
{
  ShowLo(sz);
  sprintf(szLo+14, "%2u", c+1);
  DelayInf(); Clear();
}

static void Show2(char const  *sz, uint  wPercent, uchar  c)
{
  sprintf(szLo, sz, wPercent);
  sprintf(szLo+14, "%2u", c+1);
  DelayInf(); Clear();
}

static review_wrn WarningCommon2(uint  wPrev, uint  wCurr, uchar  c)
{
  MonitorString(" "); MonitorIntDec(wPrev); MonitorString(" -> "); MonitorIntDec(wCurr);

  if ((wPrev != 0) && (wCurr == 0)) {
    Show1(szZero, c);
    MonitorString(" WARNING: value 0");
    return REVIEW_WRN_ZERO;
  }

  if (wCurr > wReviewWrnMaximum) {
    Show1(szTop, c);
    MonitorString(" WARNING: value > "); MonitorIntDec(wReviewWrnMaximum);
    return REVIEW_WRN_MAXIMUM;
  }

  if ((wPrev != 0) && (wCurr != 0)) {
    ulong dwCurrMax = (ulong)wPrev*wReviewWrnPercent/100;
    ulong dwCurrMin = (ulong)wPrev*100/wReviewWrnPercent;

    if (wCurr > dwCurrMax) {
      ulong dwPercent = (ulong)wCurr*100/wPrev;
      Show2(szPercentTop, dwPercent, c);
      MonitorString(" WARNING: value > "); MonitorLongDec(dwCurrMax); MonitorString(" "); MonitorIntDec(dwPercent); MonitorString("%%");
      return REVIEW_WRN_PERCENT_TOP;
    }

    if ((wPrev != 0) && (wCurr < dwCurrMin)) {
      ulong dwPercent = (ulong)wPrev*100/wCurr;
      Show2(szPercentBottom, dwPercent, c);
      MonitorString(" WARNING: value < "); MonitorLongDec(dwCurrMin); MonitorString(" "); MonitorIntDec(dwPercent); MonitorString("%%");
      return REVIEW_WRN_PERCENT_BOTTOM;
    }
  }

  return REVIEW_WRN_OK;
}

static review_wrn WarningRepeats2(uint  wPrev, uint  wCurr, uchar  c)
{
  MonitorString(" "); MonitorIntDec(wPrev); MonitorString(" => "); MonitorIntDec(wCurr);

  if ((wPrev != 0) && (wCurr == wPrev)) {
    Show1(szRepeat, c);
    MonitorString(" WARNING: repeat ?");
    return REVIEW_WRN_REPEAT;
  }

  return REVIEW_WRN_OK;
}


static bool WarningCommon(uint  wPrev, uint  wCurr, uchar  i)
{
  uchar c = mbRevewCanIdx[i];
  if (c == 0xFF) return false;
  if (mfReviewCan[c] != true) return false;

  review_wrn rw = WarningCommon2(wPrev, wCurr, c);
  if (rw != REVIEW_WRN_OK) {
    bReviewRepeatMax = bReviewRepeatWarning;
    fReviewIdRepeat = true;

    mcwReviewWarnings[rw]++;
    return true;
  }

  return false;
}

static bool WarningRepeats(uint  wPrev, uint  wCurr, uchar  i)
{
  uchar c = mbRevewCanIdx[i];
  if (c == 0xFF) return false;
  if (mfReviewCan[c] != true) return false;

  review_wrn rw = WarningRepeats2(wPrev, wCurr, c);
  if (rw != REVIEW_WRN_OK) {
    bReviewRepeatMax = bReviewRepeatWarning;
    fReviewIdRepeat = true;

    mcwReviewWarnings[rw]++;
    return true;
  }

  return false;
}


static bool WarningReviewBuffX6(void)
{
  MonitorString("\n");

  uchar i;
  for (i=0; i<4; i++) {
    if (WarningCommon(PrevReviewInt(5*4+i), CurrReviewInt(0*4+i), i)) return true;
  }

  uchar j;
  for (j=0; j<6-1; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (WarningCommon(CurrReviewInt(j*4+i), CurrReviewInt((j+1)*4+i), i)) return true;
    }
  }

  for (j=0; j<6; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (WarningRepeats(PrevReviewInt(j*4+i), CurrReviewInt(j*4+i), i)) return true;
    }
  }

  return false;
}

static bool WarningReviewBuffX1(void)
{
  MonitorString("\n");

  uchar i;
  for (i=0; i<4; i++) {
    if (WarningCommon(PrevReviewInt(i), CurrReviewInt(i), i)) return true;
  }

  MonitorString("\n");

  for (i=0; i<4; i++) {
    if (WarningRepeats(PrevReviewInt(i), CurrReviewInt(i), i)) return true;
  }

  return false;
}

// показывает сообщения об ошибках
bool WarningReviewBuff(uchar  bSize)
{
  switch(bSize) {
    case 0: return false;
    case 6: return WarningReviewBuffX6();
    case 1: return WarningReviewBuffX1();
    default: ASSERT(false); return false;
  }
}
