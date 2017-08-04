/*------------------------------------------------------------------------------
UNI_FLOAT,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_uni.h"
#include "../../serial/ports.h"
#include "uni_float.h"



static uchar PushDump(uchar  bCode, bool  fDouble)
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
    return 8;
  }
  else
  {
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(0xFF);
    PushChar(bCode);
    return 4;
  }
}


uchar   PushFloatOrDoubleUni(status  bStatus, double  db, bool  fDouble)
{
  if (boStrictUni == true)
  {
    switch (bStatus)
    {
      case ST_NONE:          return PushDump(0xFF, fDouble);
      case ST_NOTSUPPORTED:  return PushDump(0xFF, fDouble);
      case ST_NOTPRESENTED:  return PushDump(0xFF, fDouble);
      case ST_BADDIGITAL:    return PushDump(0xFE, fDouble);
      case ST_BADFLASH:      return PushDump(0xFF, fDouble);
      case ST_MODEM_LINK:    return PushDump(0xFE, fDouble);
      case ST_DISABLED:      return PushDump(0xFF, fDouble);
      default:                return PushFloatOrDouble(db, fDouble);
    }
  }
  else
  {
    switch (bStatus)
    {
      case ST_NONE:          return PushDump(0xE0, fDouble);
      case ST_NOTSUPPORTED:  return PushDump(0xE1, fDouble);
      case ST_NOTPRESENTED:  return PushDump(0xE2, fDouble);
      case ST_BADDIGITAL:    return PushDump(0xE3, fDouble);
      case ST_BADFLASH:      return PushDump(0xE4, fDouble);
      case ST_MODEM_LINK:    return PushDump(0xE5, fDouble);
      case ST_DISABLED:      return PushDump(0xE6, fDouble);
      default:                return PushFloatOrDouble(db, fDouble);
    }
  }
}



void    PushFloatUni(status  bStatus, float  fl)
{
  PushFloatOrDoubleUni(bStatus, fl, false);
}
