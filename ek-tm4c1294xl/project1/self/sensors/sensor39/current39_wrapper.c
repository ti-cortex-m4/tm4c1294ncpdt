/*------------------------------------------------------------------------------
current39.c


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
#include "dlms.h"
#include "caller39.h"
#include "dlms_obis.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "query_register_39.h"
#include "current39_wrapper.h"



static caller39         c;

static ulong64_         counter;
static double2          scaler;



void    DISC_Current39(void)
{
  c = InitCaller39();
  DISC();
}


void    SNRM_Current39(void)
{
  SNRM();
}


void    AARQ_Current39(void)
{
  AARQ(c.bNS, c.bNR);
}


void    RR_Current39(void)
{
  c.bNR++;
  RR(c.bNR);
}



bool    ValidateFrame_Current39(void)
{
  return ValidateFrame(c.bNS, c.bNR) == 0;
};



void    QueryValue_Current39(void)
{
  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterValueDLMS(obisEngAbs[0], c);  // TODO
}


bool    ReadValue_Current39(void)
{
  counter = ReadUnsignedValueDLSM();
  return counter.fValid;
}



void    QueryScaler_Current39(void)
{
  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterScalerDLMS(obisEngAbs[0], c); // TODO
}


bool    ReadScaler_Current39(void)
{
  scaler = ReadRegisterScalerDLMS();
  return scaler.fValid;
}



void    ReadCurrent39(void)
{
  uint64_t ddwCounter = counter.ddwValue;
  double dbScaler = scaler.dbValue;
  mpdwBaseDig[0] = ((double)ddwCounter * dbScaler / 1000) * mpdbPulseMnt[ibDig];

  MakeCurrent();
}
