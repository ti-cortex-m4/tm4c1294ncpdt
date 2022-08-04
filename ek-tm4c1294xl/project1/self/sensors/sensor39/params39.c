/*------------------------------------------------------------------------------
params34.c


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
#include "dlms.h"
#include "dlms_obis.h"
#include "error39.h"
#include "io39.h"
#include "query_register_39.h"
#include "fragment_open_39.h"
#include "dlms_read_register.h"
#include "params39.h"



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
  if (FragmentOpen39(&r) != 0) return Fault(100+0);


  double2 db2;

  db2 = ReadRegisterValueWithScaler39(obisU1, &r);
  if (!db2.fValid) return Fault(100+1);
  flU1 = db2.dbValue;

  db2 = ReadRegisterValueWithScaler39(obisU2, &r);
  if (!db2.fValid) return Fault(100+2);
  flU2 = db2.dbValue;

  db2 = ReadRegisterValueWithScaler39(obisU3, &r);
  if (!db2.fValid) return Fault(100+3);
  flU3 = db2.dbValue;


  db2 = ReadRegisterValueWithScaler39(obisI1, &r);
  if (!db2.fValid) return Fault(100+4);
  flI1 = db2.dbValue*1000;

  db2 = ReadRegisterValueWithScaler39(obisI2, &r);
  if (!db2.fValid) return Fault(100+5);
  flI2 = db2.dbValue*1000;

  db2 = ReadRegisterValueWithScaler39(obisI3, &r);
  if (!db2.fValid) return Fault(100+6);
  flI3 = db2.dbValue*1000;

/*
  db2 = ReadRegisterValueWithScaler39(obisPplus, &r);
  if (!db2.fValid) return Fault(100+7);
  flPplus = db2.dbValue;

  db2 = ReadRegisterValueWithScaler39(obisPminus, &r);
  if (!db2.fValid) return Fault(100+8);
  flPminus = db2.dbValue;


  db2 = ReadRegisterValueWithScaler39(obisQplus, &r);
  if (!db2.fValid) return Fault(100+9);
  flQplus = db2.dbValue;

  db2 = ReadRegisterValueWithScaler39(obisQminus, &r);
  if (!db2.fValid) return Fault(100+10);
  flQminus = db2.dbValue;
*/

  DISC();
  if (Input39() != SER_GOODCHECK) return Fault(100+11);

  return GetFloat0(-1);
}



float2  ReadParam39(void)
{
  Clear();

  if (fBeginParam == false)
  {
    if (!ReadParam39_Internal().fValid) return Fault(100+12);

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
