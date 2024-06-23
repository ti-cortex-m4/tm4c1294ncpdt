/*------------------------------------------------------------------------------
key_review_wrn_top.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_int_blocked.h"
#include "key_review_wrn_top.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Максимальные  ",
                        szMessage2[]    = "    значения    ",
                        szMessage3[]    = " импульсов при  ",
                        szMessage4[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetReviewWrnTop(void)
{
  key_SetIntBlocked(&chReviewWrnTop, pszMessages, REVIEW_WRN_MAXIMUM_MIN, REVIEW_WRN_MAXIMUM_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}
