/*------------------------------------------------------------------------------
key_review_read_id.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_bool_blocked.h"
#include "key_review_read_id.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "     Чтение     ",
                        szMessage2[]    = "   логических   ",
                        szMessage3[]    = "  номеров при   ",
                        szMessage4[]    = "чтении профилей ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetReviewReadId(void)
{
  key_SetBoolBlocked(&chReviewReadId, pszMessages, fReviewFlag, wSET_REVIEW_FLAG);
}

