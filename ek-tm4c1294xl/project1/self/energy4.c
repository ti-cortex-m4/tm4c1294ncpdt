/*------------------------------------------------------------------------------
ENERGY4!C


------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_energy.h"
#include "memory/mem_realtime.h"
#include "realtime/realtime.h"
#include "groups.h"
#include "energy.h"
#include "kernel/array_mnt.h"
#include "energy4.h"



float   GetPowGrpHouCurr(uchar  ibGroup, uchar  bMultiplier)
{
uchar   i, j;
float   reA, reB; 

  j = (tiCurr.bMinute % 30) / 3;
  if (j == 0) j = 10;

  reB = 0;
  for (i=1; i<=j; i++)
  {
  	LoadImpMnt((bMINUTES+iwHardMnt-i) % bMINUTES); // TODO check result
    reB += GetGrpMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ], ibGroup, bMultiplier);
  }

  reA = 10*reB/j;

  return reA;
}


float   GetPowCanHouCurr(uchar  ibCan, uchar  bMultiplier)
{
uchar   i,j;
float   reA, reB;

  j = (tiCurr.bMinute % 30) / 3;
  if (j == 0) j = 10;

  reB = 0;
  for (i=1; i<=j; i++)
  {
  	LoadImpMnt((bMINUTES+iwHardMnt-i) % bMINUTES); // TODO check result
    reB += GetCanMntInt2Real(mpwImpMntCan[ PrevSoftMnt() ], ibCan, bMultiplier);
  }

  reA = 10*reB/j;

  return reA;
}
