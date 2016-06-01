/*------------------------------------------------------------------------------
key_review_borders.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_char_blocked.h"
#include "key_review_borders.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "   Количество   ",
                        szMessage2[]    = "  повторов при  ",
                        szMessage3[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szNumberLimits, "" };



void    key_SetReviewBorders(void)
{
  key_SetCharBlocked(&chReviewBorders, pszMessages, REVIEW_BORDERS_MIN, REVIEW_BORDERS_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}
