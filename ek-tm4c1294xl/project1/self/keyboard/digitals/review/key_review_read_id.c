/*------------------------------------------------------------------------------
key_review_read_id.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_bool.h"
#include "key_review_read_id.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "Контроль времени",
                        szMessage2[]    = "  для ЦЭ6850М   ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetReviewReadId(void)
{
  key_SetBool(&chReviewReadId, pszMessages);
}

