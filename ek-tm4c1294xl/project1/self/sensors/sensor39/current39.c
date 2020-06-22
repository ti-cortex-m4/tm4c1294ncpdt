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



static uchar            bNS;
static uchar            bNR;
static uchar            bInvokeId;

static ulong            dwCurrent;



void    Query39_DISC_Current(void)
{
  bNS = 0;
  bNR = 0;
  bInvokeId = 0;

  Query39_DISC();
}


void    Query39_AARQ_Current(void)
{
  Query39_AARQ(bNS, bNR);
}


void    Query39_RR_Current(void)
{
  bNR++;
  Query39_RR(bNR);
}



bool    ValidateFrame_Current(void)
{
  return ValidateFrame(bNS, bNR) != 0;
};



void    QueryValue_Current(void)
{
  bNS++;
  bInvokeId++;
  QueryEngAbs39(bNS, bNR, bInvokeId);
}


void    ReadValue_Current(void)
{
  dwCurrent = ReadEngAbs39() % 0x100000000;
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
