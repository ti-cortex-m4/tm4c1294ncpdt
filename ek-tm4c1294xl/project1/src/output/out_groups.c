/*------------------------------------------------------------------------------
OUT_GROUPS.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_groups.h"
#include        "../memory/mem_program.h"
#include        "../serial/ports.h"
#include        "../keyboard/keyboard.h"
#include        "../groups.h"



void    OutGetGroup(void)
{
  if (bInBuff5 < bGROUPS)
    Common(&mpgrGroups[ bInBuff5 ], sizeof(group));
  else
    Result(bRES_BADADDRESS);
}


void    OutSetGroup(void)
{
uchar  i;

  if (bInBuff5 < bGROUPS)
  {
    if ( (enGlobal == GLB_PROGRAM) ||
        ((enGlobal == GLB_REPROGRAM) && (mpboUsedGroups[bInBuff5] == false)) )
    {
      for (i=0; i<bInBuff6; i++)
      {
        if ((InBuff(7+i) & 0x7F) >= bCANALS)
          break;
      }

      if (i == bInBuff6)
      {
        InitPop(6);
        Pop(&mpgrGroups[bInBuff5], sizeof(group));

        if (bInBuff5 == bGROUPS - 1)
          SaveGroups();

        boSetGroups = TRUE;

        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_NEEDPROGRAM);
  }
  else Result(bRES_BADADDRESS);
}



void    OutGetGroupsExt(void)
{
uchar   i;
uchar   wT;

  InitPushPtr();
  wT = 0;

  for (i=0; i<bGROUPS; i++)
  {
    if ((InBuff(6 + i/8) & (0x80 >> i%8)) != 0)
    {
      Push(&mpgrGroups[i], sizeof(group));
      wT += sizeof(group);
    }
  }

  OutptrOutBuff(wT);
}

