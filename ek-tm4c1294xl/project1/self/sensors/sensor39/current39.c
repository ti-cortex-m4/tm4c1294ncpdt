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



uchar                   bNS;
uchar                   bNR;
uchar                   bInvokeId;

ulong                   dwCurrent;



void    Query39_DISC_Current(void)
{
  bNS = 0;
  bNR = 0;
  bInvokeId = 0;

  Query38_DISC();
}


void    Query39_AARQ_Current(void)
{
  Query38_AARQ(bNS, bNR);
}


void    Query39_RR_Current(void)
{
  bNR++;
  Query38_RR(bNR);
}


void    QueryEngAbs39_Current(void)
{
  bNS++;
  bInvokeId++;
  QueryEngAbs39(bNS, bNR, bInvokeId);
}



bool    ValidateSframe_Current(void)
{
  return ValidateSframe(bNR);
}


bool    ValidateIframe_Current(void)
{
  return ValidateIframe(bNS, bNR);
};



void    SaveCurrent39(void)
{
  dwCurrent = ReadEngAbs39()  % 0x100000000;
}


void    ReadCurrent39(void)
{
  mpdwBaseDig[0] = dwCurrent * mpdbPulseMnt[ibDig];

  MakeCurrent();
}
