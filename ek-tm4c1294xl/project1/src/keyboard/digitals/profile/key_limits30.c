/*------------------------------------------------------------------------------
KEY_LIMITS30.C


------------------------------------------------------------------------------*/

#include        "../../../main.h"
#include        "../../../memory/mem_limits.h"
#include        "../../keyboard.h"
#include        "../../../display/display.h"
#include        "../../../digitals/limits.h"
#include        "../../key_flag.h"



//                                         0123456789ABCDEF
static char const       szUse[]         = "  Использовать  ",
                        szUseBounds[]   = "нижнюю границу ?";

                        
static char const      *pszUseBounds[]   = { szUse, szUseBounds, "" };



void    key_SetLimits30(void)
{
  key_SetFlag(&flUseBounds, pszUseBounds);
}
