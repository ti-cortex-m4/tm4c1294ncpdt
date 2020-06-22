/*------------------------------------------------------------------------------
current39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/current/current_run.h"
#include "io39.h"
#include "device39.h"
#include "query_engabs_39.h"
#include "current39.h"



static caller39         c;

static ulong64_         ddwCurrent;



void    Query39_DISC_Current(void)
{
  c = InitCaller();
  Query39_DISC();
}


void    Query39_AARQ_Current(void)
{
  Query39_AARQ(c.bNS, c.bNR);
}


void    Query39_RR_Current(void)
{
  c.bNR++;
  Query39_RR(c.bNR);
}



bool    ValidateFrame_Current(void)
{
  return ValidateFrame(c.bNS, c.bNR) != 0;
};



void    QueryValue_Current(void)
{
  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterValueDLMS(obisEngAbs, &c);
}


bool    ReadValue_Current(void)
{
  ulong64_ ddwCurrent = ReadUnsignedValueDLSM();
  return ddwCurrent.fValid;
}



void    QueryScaler_Current(void)
{
  bNS++;
  bInvokeId++;
  QueryEngAbs39(bNS, bNR, bInvokeId);
}


void    ReadScaler_Current(void)
{
  dwCurrent = ReadEngAbs39() % 0x100000000;
}



void    ReadCurrent39(void)
{
  mpdwBaseDig[0] = dwCurrent * mpdbPulseMnt[ibDig];

  MakeCurrent();
}
