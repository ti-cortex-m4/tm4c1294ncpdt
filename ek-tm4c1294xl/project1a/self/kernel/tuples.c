/*------------------------------------------------------------------------------
TUPLES,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "tuples.h"



t2uint  GetTuple2Int(uint  w1, uint  w2)
{
  t2uint tp;

  tp.w1 = w1;
  tp.w2 = w2;

  return tp;
}


t2time  GetTuple2Time(time  ti1, time  ti2)
{
  t2time tp;

  tp.ti1 = ti1;
  tp.ti2 = ti2;

  return tp;
}


factors GetFactors(double  dbTrans, double  dbPulse)
{
  factors fc;

  fc.dbTrans = dbTrans;
  fc.dbPulse = dbPulse;

  return fc;
}
