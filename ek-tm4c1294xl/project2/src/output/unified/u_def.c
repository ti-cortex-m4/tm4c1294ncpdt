/*------------------------------------------------------------------------------
U_DEF.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_energy.h"
#include "../../realtime/realtime.h"
#include "../../groups.h"
#include "u_def.h"



bool    GetDefCan(uchar  ibCan)
{
  return (mpwImpHouCan[ PrevSoftHou() ][ibCan] == 0xFFFF);
}


bool    GetDefGrp(uchar  ibGrp)
{
uchar   i;

  if (GetGroupsSize(ibGrp) == 0)
    return 0;

  for (i=0; i<GetGroupsSize(ibGrp); i++)
    if (mpwImpHouCan[ PrevSoftHou() ][ GetGroupsNodeCanal(ibGrp, i) ] == 0xFFFF)
      return 1;

  return 0;
}
