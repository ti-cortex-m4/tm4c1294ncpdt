/*------------------------------------------------------------------------------
OUT_GROUPS,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_groups.h"
#include "../memory/mem_program.h"
#include "../serial/ports.h"
#include "../settings.h"
#include "../console.h"
#include "../groups.h"



void    OutGetGroup(void)
{
  if (bInBuff5 < bGROUPS)
    Common(&mpgrGroups[ bInBuff5 ], sizeof(group));
  else
    Result(bRES_BADADDRESS);
}


void    OutSetGroup(void)
{
  if (bInBuff5 < bGROUPS)
  {
    if (enGlobal == GLB_PROGRAM)
    {
      uchar i;
      for (i=0; i<bInBuff6; i++) // размер группы
      {
        if ((InBuff(7+i) & 0x7F) >= bCANALS) // индекс канала без знака
          break;
      }

      if (i == bInBuff6)
      {
        InitPop(6);
        Pop(&mpgrGroups[bInBuff5], sizeof(group));

        if (bInBuff5 == bGROUPS - 1)
        {
          SaveGroups();

          boSetGroups = TRUE;
          SaveFile(&flSetGroups);
        }

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
  InitPushPtr();
  uint wSize = 0;

  uchar g;
  for (g=0; g<bGROUPS; g++)
  {
    if ((InBuff(6 + g/8) & (0x80 >> g%8)) != 0)
    {
      Push(&mpgrGroups[g], sizeof(group));
      wSize += sizeof(group);
    }
  }

  OutptrOutBuff(wSize);
}

