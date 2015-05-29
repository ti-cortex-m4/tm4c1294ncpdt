/*------------------------------------------------------------------------------
UNI_FLOAT,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_uni.h"
#include "../../serial/ports.h"
#include "uni_float.h"



static void PushFF(bool  fDouble)
{
  if (fDouble)
  {
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
  }
  else
  {
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
  }
}


void    PushFloatOrDoubleUni(status  bStatus, double  db, bool  fDouble)
{
  if (boStrictUni == true)
  {
    switch (bStatus)
    {
      case ST4_NONE:          PushFF(fDouble); PushChar(0xFF); break;
      case ST4_NOTSUPPORTED:  PushFF(fDouble); PushChar(0xFF); break;
      case ST4_NOTPRESENTED:  PushFF(fDouble); PushChar(0xFF); break;
      case ST4_BADDIGITAL:    PushFF(fDouble); PushChar(0xFE); break;
      case ST4_BADFLASH:      PushFF(fDouble); PushChar(0xFF); break;
      case ST4_MODEM_LINK:    PushFF(fDouble); PushChar(0xFE); break;
      case ST4_DISABLED:      PushFF(fDouble); PushChar(0xFF); break;
      default:                PushFloatOrDouble(db, fDouble); break;
    }
  }
  else
  {
    switch (bStatus)
    {
      case ST4_NONE:          PushFF(fDouble); PushChar(0xE0); break;
      case ST4_NOTSUPPORTED:  PushFF(fDouble); PushChar(0xE1); break;
      case ST4_NOTPRESENTED:  PushFF(fDouble); PushChar(0xE2); break;
      case ST4_BADDIGITAL:    PushFF(fDouble); PushChar(0xE3); break;
      case ST4_BADFLASH:      PushFF(fDouble); PushChar(0xE4); break;
      case ST4_MODEM_LINK:    PushFF(fDouble); PushChar(0xE5); break;
      case ST4_DISABLED:      PushFF(fDouble); PushChar(0xE6); break;
      default:                PushFloatOrDouble(db, fDouble); break;
    }
  }
}



void    PushFloatUni(status  bStatus, float  fl)
{
  PushFloatOrDoubleUni(bStatus, fl, false);
}
