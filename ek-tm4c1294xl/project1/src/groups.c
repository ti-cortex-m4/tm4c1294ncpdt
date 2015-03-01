/*------------------------------------------------------------------------------
GROUPS.C

 Группы
------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_groups.h"
#include        "memory/mem_program.h"
#include        "engine.h"
#include        "flash/files.h"



file const              flGroups = {FLS_GROUPS, &mpgrGroups, sizeof(group)*bGROUPS};



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



boolean SaveGroups(void)
{
  return SaveFile(&flGroups);
}


boolean LoadGroups(void)
{
  return LoadFile(&flGroups);
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

  boSetGroups = FALSE;
}
