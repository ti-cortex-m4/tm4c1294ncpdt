/*------------------------------------------------------------------------------
WRAPPERS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "wrappers.h"



float2  GetFloat2(float  flValue, bool  fValid)
{
  float2 fl2;

  fl2.flValue = flValue;
  fl2.fValid = fValid;

  return fl2;
}


double2 GetDouble2(double  dbValue, bool  fValid)
{
  double2 db2;

  db2.dbValue = dbValue;
  db2.fValid = fValid;

  return db2;
}


time2   GetTime2(time  tiValue, bool  fValid)
{
  time2 ti2;

  ti2.tiValue = tiValue;
  ti2.fValid = fValid;

  return ti2;
}
