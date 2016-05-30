/*------------------------------------------------------------------------------
key_review_wrn_trend.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_char_blocked.h"
#include "key_review_wrn_trend.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Максимальный  ",
                        szMessage2[]    = "  % отклонения  ",
                        szMessage3[]    = " импульсов при  ",
                        szMessage4[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetReviewWrnTrend(void)
{
  key_SetCharBlocked(&chReviewWrnTrend, pszMessages, REVIEW_WRN_TREND_MIN, REVIEW_WRN_TREND_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}
