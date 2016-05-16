/*------------------------------------------------------------------------------
key_review_repeats.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_char.h"
#include "key_review_repeats.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Уровень доступа ",
                        szMessage2[]    = "для Меркурий-230";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szNumberLimits, "" };



void    key_SetReviewRepeats(void)
{
  key_SetChar(&chbReviewRepeats, pszMessages, 0, 4);
}
