/*------------------------------------------------------------------------------
KEY_EXTENDED_ESC,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_1.h"
#include "../key_bool.h"
#include "key_extended_esc.h"



//                                          0123456789ABCDEF
static char const       szLoad[]         = "   «агружать    ",
                        szExtendedEscU[] = "по модему: Esc U",
                        szExtendedEscV[] = "по модему: Esc V",
                        szExtendedEscS[] = "по модему: Esc S";

static char const       *pszExtendedEscU[] = { szLoad, szExtendedEscU, "" },
                        *pszExtendedEscV[] = { szLoad, szExtendedEscV, "" },
                        *pszExtendedEscS[] = { szLoad, szExtendedEscS, "" };



void    key_SetExtendedEscU(void)
{
  key_SetBool(&flExtendedEscU, pszExtendedEscU);
}


void    key_SetExtendedEscV(void)
{
  key_SetBool(&flExtendedEscV, pszExtendedEscV);
}


void    key_SetExtendedEscS(void)
{
  key_SetBool(&flExtendedEscS, pszExtendedEscS);
}
