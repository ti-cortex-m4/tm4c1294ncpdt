/*------------------------------------------------------------------------------
key_review_flag.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_bool.h"
#include "key_review_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = " Чтение логич.  ",
                        szMessage2[]    = "  номеров при   ",
                        szMessage3[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetReviewFlag(void)
{
  key_SetBool(&chReviewFlag, pszMessages);
}

