/*------------------------------------------------------------------------------
key_review_wrn_percent.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_int_blocked.h"
#include "key_review_wrn_percent.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Максимальный  ",
                        szMessage2[]    = "  % отклонения  ",
                        szMessage3[]    = "    значений    ",
                        szMessage4[]    = " импульсов при  ",
                        szMessage5[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szNumberLimits, "" };



void    key_SetReviewWrnPercent(void)
{
  key_SetIntBlocked(&chReviewWrnPercent, pszMessages, REVIEW_WRN_PERCENT_MIN, REVIEW_WRN_PERCENT_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}
