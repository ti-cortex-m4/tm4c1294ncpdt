/*------------------------------------------------------------------------------
GROUPS.C

 Группы
------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_groups.h"
#include "memory/mem_program.h"
#include "engine.h"
#include "flash/files.h"
#include "nvram/cache.h"
#include "settings.h"
#include "groups.h"



file const              flGroups = {GROUPS, &mpgrGroups, sizeof(group)*bGROUPS};



uchar   GetGroupsSize(uchar  ibGroup)
{
  return( mpgrGroups[ibGroup].bSize );
}


void    SetGroupsSize(uchar  ibGroup, uchar  bSize)
{
  mpgrGroups[ibGroup].bSize = bSize;
}



node    GetGroupsNode(uchar  ibGroup, uchar  ibNode)
{
  return( mpgrGroups[ibGroup].mpnoNodes[ibNode] );
}


void    SetGroupsNode(uchar  ibGroup, uchar  ibNode, node  noT)
{
  mpgrGroups[ibGroup].mpnoNodes[ibNode] = noT;
}



bool    GetGroupsNodeSign(uchar  ibGroup, uchar  ibNode)
{
  return GetGroupsNode(ibGroup,ibNode).ibCanal & 0x80;
}


uchar   GetGroupsNodeCanal(uchar  ibGroup, uchar  ibNode)
{
  return GetGroupsNode(ibGroup,ibNode).ibCanal & 0x7F;
}



void    MakeUsedNodes(void)
{
uchar   i,j;

  for (i=0; i<bGROUPS; i++)
  {
    if (GetGroupsSize(i) != 0) 
      mpfUsedGroups[i] = true;
    else
      mpfUsedGroups[i] = false;
  }

  for (i=0; i<bCANALS; i++)
  {
    mpfUsedNodes[i] = false;
  }

  for (i=0; i<bGROUPS; i++)
  {
    for (j=0; j<GetGroupsSize(i); j++)
    {
      mpfUsedNodes[ GetGroupsNodeCanal(i,j) ] = true;
    }
  }
}



bool    SaveGroups(void)
{
  return SaveFile(&flGroups);
}


bool    LoadGroups(void)
{
  return LoadFile(&flGroups);
}



bool    ValidGroup(group  *pgr)
{
  uchar i;
  for (i=0; i<pgr->bSize; i++)
  {
    if ((pgr->mpnoNodes[i].ibCanal & 0x7F) >= bCANALS)
      return false;
  }

  return true;
}



void    InitGroups(void)
{
  LoadGroups();
  MakeUsedNodes();
}


void    ResetGroups(void)
{
uchar   i;
node    noT;

  memset(&mpgrGroups, 0, sizeof(mpgrGroups));

  for (i=0; i<bGROUPS; i++)
  {
    if ((i < 16) && (i < bCANALS))
    {
      SetGroupsSize(i,1);

      noT.ibCanal = i;
      SetGroupsNode(i,0, noT);
    }
    else SetGroupsSize(i,0);
  }

  SaveFile(&flGroups);

  MakeUsedNodes();

  boSetGroups = false;
  SaveCache(&chSetGroups);
}
