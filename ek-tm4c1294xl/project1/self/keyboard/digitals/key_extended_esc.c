/*------------------------------------------------------------------------------
KEY_EXTENDED_ESC,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_1.h"
#include "../common/key_bool.h"
#include "key_extended_esc.h"



//                                          0123456789ABCDEF
static char const       szLoad[]         = "   ���������    ",
                        szExtendedEscU[] = "�� ������: Esc U",
                        szExtendedEscV[] = "�� ������: Esc V",
                        szExtendedEscS[] = "�� ������: Esc S";

static char const       *pszExtendedEscU[] = { szLoad, szExtendedEscU, "" },
                        *pszExtendedEscV[] = { szLoad, szExtendedEscV, "" },
                        *pszExtendedEscS[] = { szLoad, szExtendedEscS, "" };



void    key_SetExtendedEscU(void)
{
  key_SetBool(&chExtendedEscU, pszExtendedEscU);
}


void    key_SetExtendedEscV(void)
{
  key_SetBool(&chExtendedEscV, pszExtendedEscV);
}


void    key_SetExtendedEscS(void)
{
  key_SetBool(&chExtendedEscS, pszExtendedEscS);
}
