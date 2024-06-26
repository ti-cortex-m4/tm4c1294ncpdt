/*------------------------------------------------------------------------------
key_review_borders.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_char_blocked.h"
#include "key_review_borders.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Проверочное   ",
                        szMessage2[]    = "   количество   ",
                        szMessage3[]    = "  повторов при  ",
                        szMessage4[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetReviewRepeatWarning(void)
{
  key_SetCharBlocked(&chReviewRepeatWarning, pszMessages, REVIEW_REPEAT_WARNING_MIN, REVIEW_REPEAT_WARNING_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}
