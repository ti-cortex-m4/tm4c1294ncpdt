/*------------------------------------------------------------------------------
OUT_GROUPS.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_groups.h"
#include        "../memory/mem_program.h"
#include        "../ports.h"
#include        "../keyboard.h"
#include        "../groups.h"



void    OutGetGroup(void)
{
  if (bInBuff5 < bGROUPS)
    Common(&mpgrGroups[ bInBuff5 ], sizeof(groups));
  else
    Result(bRES_BADADDRESS);
}


void    OutSetGroup(void)
{
uchar  i;

  if (bInBuff5 < bGROUPS)
  {
    if ( (enGlobal == GLB_PROGRAM) ||
        ((enGlobal == GLB_REPROGRAM) && (mpboUsedGroups[bInBuff5] == boFalse)) )
    {
      for (i=0; i<bInBuff6; i++)
      {
        if ((InBuff(7+i) & 0x7F) >= bCANALS)
          break;
      }

      if (i == bInBuff6)
      {
        InitPop(6);
        Pop(&mpgrGroups[bInBuff5], sizeof(groups));

        if (bInBuff5 == bGROUPS - 1)
          SaveGroups();

        boSetGroups = boTrue;

        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_NEEDPROGRAM);
  }
  else Result(bRES_BADADDRESS);
}
