/*------------------------------------------------------------------------------
params34*c


------------------------------------------------------------------------------*/

#include <math.h>
#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../digitals/params/params.h"
#include "../../digitals/params/params2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "device39.h"
#include "error39.h"
#include "io39.h"
#include "query_register_39.h"
#include "fragment_open_39.h"
#include "dlms_read_register.h"
#include "params39.h"



// Blue Book: 7.5.1 Value group C codes – Electricity
static const obis_t obisU1      = {1, 0, 32, 7, 0, 255},
                    obisU2      = {1, 0, 52, 7, 0, 255},
                    obisU3      = {1, 0, 72, 7, 0, 255},

                    obisI1      = {1, 0, 31, 7, 0, 255},
                    obisI2      = {1, 0, 51, 7, 0, 255},
                    obisI3      = {1, 0, 71, 7, 0, 255},

                    obisPplus   = {1, 0,  1, 7, 0, 255},
                    obisPminus  = {1, 0,  2, 7, 0, 255},

                    obisQplus   = {1, 0,  3, 7, 0, 255},
                    obisQminus  = {1, 0,  4, 7, 0, 255};



static float        flU1, flU2, flU3,
                    flI1, flI2, flI3,
                    flPplus, flPminus,
                    flQplus, flQminus;



static float2 Fault(uchar  bError)
{
  return GetFloat2Error1(Error39(bError));
}



float2  ReadParam39_Internal(void)
{
  caller39 r = InitCaller39();
  if (FragmentOpen39(&r) != 0) return Fault(110+0);


  double2 db2;

  db2 = ReadRegisterValueWithScaler39(obisU1, &r);
  if (!db2.fValid) return Fault(110+1);
  flU1 = db2.dbValue;

  db2 = ReadRegisterValueWithScaler39(obisU2, &r);
  if (!db2.fValid) return Fault(110+2);
  flU2 = db2.dbValue;

  db2 = ReadRegisterValueWithScaler39(obisU3, &r);
  if (!db2.fValid) return Fault(110+3);
  flU3 = db2.dbValue;


  db2 = ReadRegisterValueWithScaler39(obisI1, &r);
  if (!db2.fValid) return Fault(110+4);
  flI1 = db2.dbValue*1000;

  db2 = ReadRegisterValueWithScaler39(obisI2, &r);
  if (!db2.fValid) return Fault(110+5);
  flI2 = db2.dbValue*1000;

  db2 = ReadRegisterValueWithScaler39(obisI3, &r);
  if (!db2.fValid) return Fault(110+6);
  flI3 = db2.dbValue*1000;


  db2 = ReadRegisterValueWithScaler39(obisPplus, &r);
  if (!db2.fValid) return Fault(110+7);
  flPplus = db2.dbValue;

  db2 = ReadRegisterValueWithScaler39(obisPminus, &r);
  if (!db2.fValid) return Fault(110+8);
  flPminus = db2.dbValue;


  db2 = ReadRegisterValueWithScaler39(obisQplus, &r);
  if (!db2.fValid) return Fault(110+9);
  flQplus = db2.dbValue;

  db2 = ReadRegisterValueWithScaler39(obisQminus, &r);
  if (!db2.fValid) return Fault(110+10);
  flQminus = db2.dbValue;


  Query39_DISC();
  if (Input39() != SER_GOODCHECK) return Fault(110+11);

  return GetFloat0(-1);
}



float2  ReadParam39(void)
{
  Clear();

  if (fBeginParam == false)
  {
    if (!ReadParam39_Internal().fValid) return Fault(110+12);

    fBeginParam = true;
  }

  switch (diCurr.ibLine)
  {
    case PAR_U1 : return GetFloat0(flU1);
    case PAR_U2 : return GetFloat0(flU2);
    case PAR_U3 : return GetFloat0(flU3);

    case PAR_I1 : return GetFloat0(flI1);
    case PAR_I2 : return GetFloat0(flI2);
    case PAR_I3 : return GetFloat0(flI3);

    case PAR_P  : return GetFloat0(flPplus-flPminus);

    case PAR_Q  : return GetFloat0(flQplus-flQminus);

    case PAR_S  : return GetFloat0(CalcS(flPplus-flPminus, flQplus-flQminus));

    default: return GetFloat2Error();
  }
}



#ifdef MONITOR_39

double2 TestParam39(void)
{
  MonitorOpen(0);

  ReadParam39_Internal();

  return GetDouble2(0, true);
}

#endif
