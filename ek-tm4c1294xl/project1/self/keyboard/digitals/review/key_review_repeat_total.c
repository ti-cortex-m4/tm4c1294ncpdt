/*------------------------------------------------------------------------------
key_review_repeat_total.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_char_blocked.h"
#include "key_review_repeat_total.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Максимальное  ",
                        szMessage2[]    = "   количество   ",
                        szMessage3[]    = "  повторов при  ",
                        szMessage4[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetReviewRepeatTotal(void)
{
  key_SetCharBlocked(&chReviewRepeatTotal, pszMessages, REVIEW_REPEAT_TOTAL_MIN, REVIEW_REPEAT_TOTAL_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}
