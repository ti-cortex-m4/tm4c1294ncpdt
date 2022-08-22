/*------------------------------------------------------------------------------
current39.c


------------------------------------------------------------------------------*/

#include <math.h>
#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/current/current_run.h"
#include "io40.h"
#include "dlms.h"
#include "caller40.h"
#include "dlms_obis.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "query_register_39.h"
#include "current40_wrapper.h"



static uchar            ibLine40;

static caller40         c;

static ulong64_         counter[4];
static double2          dbScaler;



void    ClearLine40(void)
{
  ibLine40 = 0;
}


uchar   IncLine40(void)
{
  return ++ibLine40;
}


uchar   GetLine40(void)
{
  return ibLine40;
}



void    DISC_Current40(void)
{
  c = InitCaller40();
  DISC();
}


void    SNRM_Current40(void)
{
  SNRM();
}


void    AARQ_Current40(void)
{
  AARQ(c.bNS, c.bNR);
}


void    RR_Current40(void)
{
  c.bNR++;
  RR(c.bNR);
}



bool    ValidateFrame_Current40(void)
{
  return ValidateFrame(c.bNS, c.bNR) == 0;
}



void    QueryValue_Current40(void)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n QueryValue_Current40 ");  MonitorCharDec(ibLine40);
#endif

  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterValueDLMS(obisEngAbs[ibLine40], c);
}


bool    ReadValue_Current40(void)
{
  counter[ibLine40] = ReadUnsignedValueDLSM();
  return counter[ibLine40].fValid;
}



void    QueryScaler_Current40(void)
{
#ifdef MONITOR_40_NAMES
  MonitorString("\n\n QueryScaler_Current40 ");
#endif

  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterScalerDLMS(obisEngAbs[0], c);
}


bool    ReadScaler_Current40(void)
{
  dbScaler = ReadRegisterScalerDLMS();
  return dbScaler.fValid;
}



void    ReadCurrent40(void)
{
  double scaler = dbScaler.dbValue;

  uchar i;
  for (i=0; i<4; i++)
  {
    uint64_t ddwCounter = counter[i].ddwValue;
    mpdwBaseDig[i] = ((double)ddwCounter * scaler / 1000) * mpdbPulseMnt[ibDig];
  }

  MakeCurrent();
}
