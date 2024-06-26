/*------------------------------------------------------------------------------
key_review_wrn_maximum.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_int_blocked.h"
#include "key_review_wrn_maximum.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  ������������  ",
                        szMessage2[]    = "    ��������    ",
                        szMessage3[]    = " ��������� ���  ",
                        szMessage4[]    = "������ �������� ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetReviewWrnMaximum(void)
{
  key_SetIntBlocked(&chReviewWrnMaximum, pszMessages, REVIEW_WRN_MAXIMUM_MIN, REVIEW_WRN_MAXIMUM_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}