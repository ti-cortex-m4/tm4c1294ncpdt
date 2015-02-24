/*------------------------------------------------------------------------------
GROUPS.C

 Группы
------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_groups.h"
#include        "memory/mem_program.h"
#include        "engine.h"
#include        "flash/files.h"
#include        "include/flash.h"



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
      mpboUsedGroups[i] = TRUE;
    else
      mpboUsedGroups[i] = FALSE;
  }

  for (i=0; i<bCANALS; i++)
    mpboUsedNodes[i] = FALSE;

  for (i=0; i<bGROUPS; i++)
  {
    for (j=0; j<GetGroupsSize(i); j++)
      mpboUsedNodes[ GetGroupsNodeCanal(i,j) ] = TRUE;
  }
}



bool    SaveGroups(void)
{
  OpenOut(DF_GROUPS);

  if (Save(mpgrGroups, sizeof(group)*bGROUPS) == 0)
    return(0);

  return CloseOut();
}


bool    LoadGroups(void)
{
  OpenIn(DF_GROUPS);
  return Load(mpgrGroups, sizeof(group)*bGROUPS);
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

  SaveGroups();

  MakeUsedNodes();

  boSetGroups = FALSE;
}
