/*------------------------------------------------------------------------------
ENERGY4.C


------------------------------------------------------------------------------*/

#include "main.h"
//#include "engine.h"
//#include "memory/mem_factors.h"
#include "memory/mem_energy.h"
//#include "memory/mem_energy_spec.h"
//#include "memory/mem_groups.h"
//#include "memory/mem_tariffs.h"
#include "memory/mem_realtime.h"
//#include "memory/mem_current.h"
//#include "memory/mem_special.h"
//#include "digitals/digitals.h"
//#include "digitals/sensors.h"
#include "realtime/realtime.h"
#include "groups.h"
#include "energy.h"
#include "energy2.h"
#include "energy4.h"



real    GetPowGrpHouCurr(uchar  ibGroup, uchar  bMul)
{
uchar   i, j;
real    reA, reB; 

  j = (tiCurr.bMinute % 30) / 3;
  if (j == 0) j = 10;

  reB = 0;
  for (i=1; i<=j; i++)
  {
  	LoadImpMnt((bMINUTES+ibHardMnt-i) % bMINUTES); // TODO check result
    reB += GetGrpMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ], ibGroup, bMul);
  }

  reA = 10*reB/j;

  return reA;
}


real    GetPowCanHouCurr(uchar  ibCan, uchar  bMul)
{
uchar   i,j;
real    reA, reB;

  j = (tiCurr.bMinute % 30) / 3;
  if (j == 0) j = 10;

  reB = 0;
  for (i=1; i<=j; i++)
  {
  	LoadImpMnt((bMINUTES+ibHardMnt-i) % bMINUTES); // TODO check result
    reB += GetCanMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ], ibCan, bMul);
  }

  reA = 10*reB/j;

  return reA;
}
