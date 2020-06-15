/*------------------------------------------------------------------------------
WRAPPERS,C

 Значения с флагом достоверности
------------------------------------------------------------------------------*/

#include "../main.h"
#include "wrappers.h"



schar2  GetSChar2(schar  bValue, bool  fValid)
{
  schar2 b2;

  b2.bValue = bValue;
  b2.fValid = fValid;

  return b2;
}


schar2  GetSChar2Error(void)
{
  return GetSChar2(-1, false);
}



ulong2  GetLong2(ulong  dwValue, bool  fValid)
{
  ulong2 dw2;

  dw2.dwValue = dwValue;
  dw2.fValid = fValid;

  return dw2;
}


ulong2  GetLong2Error(void)
{
  return GetLong2(MAX_LONG, false);
}



ulong64_ GetLong64(uint64_t  ddwValue, bool  fValid, uchar  bError)
{
  ulong64_ ddw2;

  ddw2.ddwValue = ddwValue;
  ddw2.fValid = fValid;
  ddw2.bError = bError;

  return ddw2;
}


ulong64_ GetLong64Error(uchar  bError)
{
  return GetLong64(MAX_LONGLONG, false, bError);
}



ulong64_ GetSignedLong64(int64_t  ddwValue, bool  fValid, uchar  bError)
{
  ulong64_ ddw2;

  ddw2.ddwValue = ddwValue;
  ddw2.fValid = fValid;
  ddw2.bError = bError;

  return ddw2;
}


ulong64_ GetSignedLong64Error(uchar  bError)
{
  return GetSignedLong64(MAX_LONGLONG, false, bError);
}



float2  GetFloat2(float  flValue, bool  fValid)
{
  float2 fl2;

  fl2.flValue = flValue;
  fl2.fValid = fValid;

  return fl2;
}


float2  GetFloat2Error(void)
{
  return GetFloat2(-1, false);
}



double2 GetDouble2(double  dbValue, bool  fValid)
{
  double2 db2;

  db2.dbValue = dbValue;
  db2.fValid = fValid;

  return db2;
}


double2 GetDouble2Error(void)
{
  return GetDouble2(-1, false);
}



time2   GetTime2(time  tiValue, bool  fValid)
{
  time2 ti2;

  ti2.tiValue = tiValue;
  ti2.fValid = fValid;

  return ti2;
}


time2   GetTime2Error(void)
{
  static const time tiZero = { 0, 0, 0, 0, 0, 0 };
  return GetTime2(tiZero, false);
}



factors2 GetFactors2(factors  fcValue, bool  fValid)
{
  factors2 fc2;

  fc2.fcValue = fcValue;
  fc2.fValid = fValid;

  return fc2;
}


factors2 GetFactors2Error(void)
{
  return GetFactors2(GetFactors(-1,-1), false);
}
