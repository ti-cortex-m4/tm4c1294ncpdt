/*------------------------------------------------------------------------------
UNI_FLOAT,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_uni.h"
#include "../../serial/ports.h"
#include "uni_float.h"



static void PushDump(uchar  bCode, bool  fDouble)
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
    PushChar(bCode);
  }
  else
  {
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(bCode);
  }
}


void    PushFloatOrDoubleUni(status  bStatus, double  db, bool  fDouble)
{
  if (boStrictUni == true)
  {
    switch (bStatus)
    {
      case ST4_NONE:          PushDump(0xFF, fDouble); break;
      case ST4_NOTSUPPORTED:  PushDump(0xFF, fDouble); break;
      case ST4_NOTPRESENTED:  PushDump(0xFF, fDouble); break;
      case ST4_BADDIGITAL:    PushDump(0xFE, fDouble); break;
      case ST4_BADFLASH:      PushDump(0xFF, fDouble); break;
      case ST4_MODEM_LINK:    PushDump(0xFE, fDouble); break;
      case ST4_DISABLED:      PushDump(0xFF, fDouble); break;
      default:                PushFloatOrDouble(db, fDouble); break;
    }
  }
  else
  {
    switch (bStatus)
    {
      case ST4_NONE:          PushDump(0xE0, fDouble); break;
      case ST4_NOTSUPPORTED:  PushDump(0xE1, fDouble); break;
      case ST4_NOTPRESENTED:  PushDump(0xE2, fDouble); break;
      case ST4_BADDIGITAL:    PushDump(0xE3, fDouble); break;
      case ST4_BADFLASH:      PushDump(0xE4, fDouble); break;
      case ST4_MODEM_LINK:    PushDump(0xE5, fDouble); break;
      case ST4_DISABLED:      PushDump(0xE6, fDouble); break;
      default:                PushFloatOrDouble(db, fDouble); break;
    }
  }
}



void    PushFloatUni(status  bStatus, float  fl)
{
  PushFloatOrDoubleUni(bStatus, fl, false);
}
