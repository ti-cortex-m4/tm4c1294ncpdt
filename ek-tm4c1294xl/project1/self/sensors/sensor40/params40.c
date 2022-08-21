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
#include "error40.h"
#include "io39.h"
#include "query_register_39.h"
#include "fragment_open_39.h"
#include "dlms_read_register.h"
#include "params40.h"



static float        flU1, flU2, flU3,
                    flI1, flI2, flI3,
                    flP, flP1, flP2, flP3,
                    flQ, flQ1, flQ2, flQ3,
                    flS, flS1, flS2, flS3,
                    flF,
                    flC, flC1, flC2, flC3;



static float2 Fault(uchar  bError)
{
  return GetFloat2Error1(Error40(bError));
}



float2  ReadParam40_Internal(void)
{
  caller40 r = InitCaller40();
  if (FragmentOpen40(&r) != 0) return Fault(100+0);


  double2 db2;

  db2 = ReadRegisterSignedValueWithScaler39(obisU1, &r);
  if (!db2.fValid) return Fault(100+1);
  flU1 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisU2, &r);
  if (!db2.fValid) return Fault(100+1);
  flU2 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisU3, &r);
  if (!db2.fValid) return Fault(100+1);
  flU3 = db2.dbValue;


  db2 = ReadRegisterSignedValueWithScaler39(obisI1, &r);
  if (!db2.fValid) return Fault(100+2);
  flI1 = db2.dbValue*1000;

  db2 = ReadRegisterSignedValueWithScaler39(obisI2, &r);
  if (!db2.fValid) return Fault(100+2);
  flI2 = db2.dbValue*1000;

  db2 = ReadRegisterSignedValueWithScaler39(obisI3, &r);
  if (!db2.fValid) return Fault(100+2);
  flI3 = db2.dbValue*1000;


  db2 = ReadRegisterSignedValueWithScaler39(obisP, &r);
  if (!db2.fValid) return Fault(100+3);
  flP = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisP1, &r);
  if (!db2.fValid) return Fault(100+3);
  flP1 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisP2, &r);
  if (!db2.fValid) return Fault(100+3);
  flP2 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisP3, &r);
  if (!db2.fValid) return Fault(100+3);
  flP3 = db2.dbValue;


  db2 = ReadRegisterSignedValueWithScaler39(obisQ, &r);
  if (!db2.fValid) return Fault(100+4);
  flQ = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisQ1, &r);
  if (!db2.fValid) return Fault(100+4);
  flQ1 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisQ2, &r);
  if (!db2.fValid) return Fault(100+4);
  flQ2 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisQ3, &r);
  if (!db2.fValid) return Fault(100+4);
  flQ3 = db2.dbValue;


  db2 = ReadRegisterSignedValueWithScaler39(obisS, &r);
  if (!db2.fValid) return Fault(100+5);
  flS = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisS1, &r);
  if (!db2.fValid) return Fault(100+5);
  flS1 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisS2, &r);
  if (!db2.fValid) return Fault(100+5);
  flS2 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisS3, &r);
  if (!db2.fValid) return Fault(100+5);
  flS3 = db2.dbValue;


  db2 = ReadRegisterSignedValueWithScaler39(obisF, &r);
  if (!db2.fValid) return Fault(100+6);
  flF = db2.dbValue;


  db2 = ReadRegisterSignedValueWithScaler39(obisC, &r);
  if (!db2.fValid) return Fault(100+7);
  flC = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisC1, &r);
  if (!db2.fValid) return Fault(100+7);
  flC1 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisC2, &r);
  if (!db2.fValid) return Fault(100+7);
  flC2 = db2.dbValue;

  db2 = ReadRegisterSignedValueWithScaler39(obisC3, &r);
  if (!db2.fValid) return Fault(100+7);
  flC3 = db2.dbValue;


  DISC();
  if (Input39() != SER_GOODCHECK) return Fault(100+8);

  return GetFloat0(-1);
}



float2  ReadParam40(void)
{
  Clear();

  if (fBeginParam == false)
  {
    if (!ReadParam40_Internal().fValid) return Fault(100+9);

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

    case PAR_C  : return GetFloat0(flC);
    case PAR_C1 : return GetFloat0(flC1);
    case PAR_C2 : return GetFloat0(flC2);
    case PAR_C3 : return GetFloat0(flC3);

    default: return GetFloat2Error();
  }
}



#ifdef MONITOR_40

double2 TestParam39(void)
{
  MonitorOpen(0);

  ReadParam40_Internal();

  return GetDouble2(0, true);
}

#endif
