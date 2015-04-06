/*------------------------------------------------------------------------------
U_FLOAT.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_uni.h"
#include        "../../serial/ports.h"
#include        "u_float.h"



static void PushFFFFFF(void)
{
  PushChar(0xFF); PushChar(0xFF); PushChar(0xFF);
}


void    PushRealUni(status4  status, real  *preT)
{
  if (boStrictUni == TRUE)
  {
    switch (status)
    {
      case ST4_NONE:          PushFFFFFF(); PushChar(0xFF); break;
      case ST4_NOTSUPPORTED:  PushFFFFFF(); PushChar(0xFF); break;
      case ST4_NOTPRESENTED:  PushFFFFFF(); PushChar(0xFF); break;
      case ST4_BADDIGITAL:    PushFFFFFF(); PushChar(0xFE); break;
      case ST4_BADFLASH:      PushFFFFFF(); PushChar(0xFF); break;
      case ST4_BADPORT:       PushFFFFFF(); PushChar(0xFE); break;
      case ST4_BADENABLING:   PushFFFFFF(); PushChar(0xFF); break;
      default:                Push(preT, sizeof(real)); break;
    }
  }
  else
  {
    switch (status)
    {
      case ST4_NONE:          PushFFFFFF(); PushChar(0xE0); break;
      case ST4_NOTSUPPORTED:  PushFFFFFF(); PushChar(0xE1); break;
      case ST4_NOTPRESENTED:  PushFFFFFF(); PushChar(0xE2); break;
      case ST4_BADDIGITAL:    PushFFFFFF(); PushChar(0xE3); break;
      case ST4_BADFLASH:      PushFFFFFF(); PushChar(0xE4); break;
      case ST4_BADPORT:       PushFFFFFF(); PushChar(0xE5); break;
      case ST4_BADENABLING:   PushFFFFFF(); PushChar(0xE6); break;
      default:                Push(preT, sizeof(real)); break;
    }
  }
}
