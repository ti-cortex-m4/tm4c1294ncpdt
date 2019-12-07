/*------------------------------------------------------------------------------
key_auto_flow_enbl.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../common/key_bool.h"
#include "key_auto_flow_enbl.h"



//                                          0123456789ABCDEF
static char const       szMessage[]      = "Параметры ?     ";

static char const       *pszMessages[]   = { szMessage, "" };



void    key_SetAutoFlowEnbl(void)
{
  key_SetBool(&chAutoFlowEnbl, pszMessages);
}
