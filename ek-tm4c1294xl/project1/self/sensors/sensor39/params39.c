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
                    flP, flP1, flP2, flP3,
                    flQ, flQ1, flQ2, flQ3,
                    flS, flS1, flS2, flS3,
                    flF;



static float2 Fault(uchar  bError)
{
  return GetFloat2Error1(Error39(bError));
}



float2  ReadParam39_Internal(void)
{
  caller39 r = InitCaller39();
  if (FragmentOpen39(&r) != 0) return Fault(100+0);


  double2 db2;

  db2 = ReadRegisterSignedValueWithScaler39(obisU1, &r);
  if (!db2.fValid) return Fault(100+1);
  flU1 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisU2, &r);
  if (!db2.fValid) return Fault(100+2);
  flU2 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisU3, &r);
  if (!db2.fValid) return Fault(100+3);
  flU3 = db2.dbValue;


  db2 = ReadRegisterSignedValueWithScaler39(obisI1, &r);
  if (!db2.fValid) return Fault(100+4);
  flI1 = db2.dbValue*1000;

  db2 = ReadRegisterSignedValueWithScaler39(obisI2, &r);
  if (!db2.fValid) return Fault(100+5);
  flI2 = db2.dbValue*1000;

  db2 = ReadRegisterSignedValueWithScaler39(obisI3, &r);
  if (!db2.fValid) return Fault(100+6);
  flI3 = db2.dbValue*1000;


  db2 = ReadRegisterSignedValueWithScaler39(obisP, &r);
  if (!db2.fValid) return Fault(100+4);
  flP = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisP1, &r);
  if (!db2.fValid) return Fault(100+4);
  flP1 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisP2, &r);
  if (!db2.fValid) return Fault(100+5);
  flP2 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisP3, &r);
  if (!db2.fValid) return Fault(100+6);
  flP3 = db2.dbValue;


  db2 = ReadRegisterSignedValueWithScaler39(obisQ, &r);
  if (!db2.fValid) return Fault(100+4);
  flQ = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisQ1, &r);
  if (!db2.fValid) return Fault(100+4);
  flQ1 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisQ2, &r);
  if (!db2.fValid) return Fault(100+5);
  flQ2 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisQ3, &r);
  if (!db2.fValid) return Fault(100+6);
  flQ3 = db2.dbValue;


  db2 = ReadRegisterSignedValueWithScaler39(obisS, &r);
  if (!db2.fValid) return Fault(100+4);
  flS = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisS1, &r);
  if (!db2.fValid) return Fault(100+4);
  flS1 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisS2, &r);
  if (!db2.fValid) return Fault(100+5);
  flS2 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisS3, &r);
  if (!db2.fValid) return Fault(100+6);
  flS3 = db2.dbValue;


  db2 = ReadRegisterSignedValueWithScaler39(obisF, &r);
  if (!db2.fValid) return Fault(100+7);
  flF = db2.dbValue;


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

    case PAR_P  : return GetFloat0(flP);
    case PAR_P1 : return GetFloat0(flP1);
    case PAR_P2 : return GetFloat0(flP2);
    case PAR_P3 : return GetFloat0(flP3);

    case PAR_Q  : return GetFloat0(flQ);
    case PAR_Q1 : return GetFloat0(flQ1);
    case PAR_Q2 : return GetFloat0(flQ2);
    case PAR_Q3 : return GetFloat0(flQ3);

    case PAR_S  : return GetFloat0(flS);
    case PAR_S1 : return GetFloat0(flS1);
    case PAR_S2 : return GetFloat0(flS2);
    case PAR_S3 : return GetFloat0(flS3);

    case PAR_F  : return GetFloat0(flF);

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
