/*------------------------------------------------------------------------------
KEY_SHORT_PROFILE_C.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  Размер блока  ",
                        szMessage2[]    = "   при опросе   ",
                        szMessage3[]    = "     СС-301     ",
                        szTrue[]        = " 1 получас      ",
                        szFalse[]       = " 6 получасов    ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetShortProfileC(void)
{
  key_SetFlag(&chShortProfileC, pszMessages, szTrue, szFalse);
}

