/*------------------------------------------------------------------------------
current39*c


------------------------------------------------------------------------------*/

#include <math.h>
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
#include "device39_obis.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "query_register_39.h"
#include "current39.h"



static caller39         c;

static ulong64_         value2;
static slong64_         scaler;



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
  return ValidateFrame(c.bNS, c.bNR) == 0;
};



void    QueryValue_Current(void)
{
  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterValueDLMS(obisEngAbs, c);
}


bool    ReadValue_Current(void)
{
  value2 = ReadUnsignedValueDLSM();
  return value2.fValid;
}



void    QueryScaler_Current(void)
{
  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterScalerDLMS(obisEngAbs, c);
}


bool    ReadScaler_Current(void)
{
  scaler = ReadRegisterScalerDLMS();
  return scaler.fValid;
}



void    ReadCurrent39(void)
{
  uint64_t ddwValue = value2.ddwValue;
  double dbScaler = pow(10, scaler.ddwValue);
  mpdwBaseDig[0] = ((double)ddwValue * dbScaler / 1000) * mpdbPulseMnt[ibDig];

  MakeCurrent();
}
