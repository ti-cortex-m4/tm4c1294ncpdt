/*------------------------------------------------------------------------------
TUPLES,H


------------------------------------------------------------------------------*/

#ifndef __TUPLES
#define __TUPLES


typedef struct
{
  uint          w1;
  uint          w2;
} t2uint;


typedef struct
{
  time          ti1;
  time          ti2;
} t2time;


typedef struct
{
  double        dbTrans;
  double        dbPulse;
} factors;


t2uint  GetTuple2Int(uint  w1, uint  w2);
t2time  GetTuple2Time(time  ti1, time  ti2);
factors GetFactors(double  dbTrans, double  dbPulse);


#endif
