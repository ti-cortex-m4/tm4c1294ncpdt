/*------------------------------------------------------------------------------
key_review_margins.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_char.h"
#include "key_review_margins.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Макс. количество",
                        szMessage2[]    = "  повторов при  ",
                        szMessage3[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szNumberLimits, "" };



void    key_SetReviewMargins(void)
{
  key_SetChar(&chReviewMargins, pszMessages, REVIEW_MARGINS_MIN, REVIEW_MARGINS_MAX);
}
