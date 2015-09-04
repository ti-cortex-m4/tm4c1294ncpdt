/*------------------------------------------------------------------------------
GROUPS.C

 Группы
------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_groups.h"
#include "memory/mem_program.h"
#include "nvram/cache.h"
#include "settings.h"
#include "groups.h"



cache const             chGroups = {GROUPS, &mpgrGroups, sizeof(mpgrGroups)};



uchar   GetGroupsSize(uchar  ibGrp)
{
  return mpgrGroups[ibGrp].bSize;
}


void    SetGroupsSize(uchar  ibGrp, uchar  bSize)
{
  mpgrGroups[ibGrp].bSize = bSize;
}



node    GetGroupsNode(uchar  ibGrp, uchar  ibNode)
{
  return mpgrGroups[ibGrp].mpnoNodes[ibNode];
}


void    SetGroupsNode(uchar  ibGrp, uchar  ibNode, node  nd)
{
  mpgrGroups[ibGrp].mpnoNodes[ibNode] = nd;
}



bool    GetGroupsNodeSign(uchar  ibGrp, uchar  ibNode)
{
  return GetGroupsNode(ibGrp,ibNode).ibCanal & 0x80;
}


uchar   GetGroupsNodeCanal(uchar  ibGrp, uchar  ibNode)
{
  return GetGroupsNode(ibGrp,ibNode).ibCanal & 0x7F;
}



void    MakeUsedNodes(void)
{
  uchar g;
  for (g=0; g<bGROUPS; g++)
  {
    if (GetGroupsSize(g) != 0) 
      mpfUsedGroups[g] = true;
    else
      mpfUsedGroups[g] = false;
  }

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpfUsedNodes[c] = false;
  }

  for (g=0; g<bGROUPS; g++)
  {
    for (c=0; c<GetGroupsSize(g); c++)
    {
      mpfUsedNodes[ GetGroupsNodeCanal(g,c) ] = true;
    }
  }
}



bool    SaveGroups(void)
{
  return SaveCache(&chGroups);
}


bool    LoadGroups(void)
{
  return LoadCache(&chGroups);
}



bool    IsValidGroup(group  *pgr)
{
  uchar c;
  for (c=0; c<pgr->bSize; c++)
  {
    if ((pgr->mpnoNodes[c].ibCanal & 0x7F) >= bCANALS)
      return false;
  }

  return true;
}



void    InitGroups(void)
{
  LoadGroups();

  if (enGlobal == GLB_WORK)
    MakeUsedNodes();
}


void    ResetGroups(void)
{
  memset(&mpgrGroups, 0, sizeof(mpgrGroups));

  uchar g;
  for (g=0; g<bGROUPS; g++)
  {
    if (g < 16)
    {
      SetGroupsSize(g,1);

      node nd;
      nd.ibCanal = g;

      SetGroupsNode(g,0,nd);
    }
    else SetGroupsSize(g,0);
  }

  SaveCache(&chGroups);

  boSetGroups = false;
  SaveCache(&chSetGroups);
}
