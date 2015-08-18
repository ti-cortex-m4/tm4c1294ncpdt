/*------------------------------------------------------------------------------
TUPLES,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "tuples.h"



tuple2uint  GetTuple2Uint(uint  w1,  uint  w2)
{
  tuple2uint tp;
  tp.w1 = w1;
  tp.w2 = w2;
  return tp;
}


tuple2time  GetTuple2Time(time  ti1,  time  ti2)
{
  tuple2time tp;
  tp.ti1 = ti1;
  tp.ti2 = ti2;
  return tp;
}
