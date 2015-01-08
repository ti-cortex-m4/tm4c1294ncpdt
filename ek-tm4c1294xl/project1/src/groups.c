/*------------------------------------------------------------------------------
GROUPS.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "mem_groups.h"
#include        "mem_program.h"
#include        "engine.h"



uchar   GetGroupsSize(uchar  ibGroup)
{
  return( mpgrGroups[ibGroup].bSize );
}


void    SetGroupsSize(uchar  ibGroup, uchar  bSize)
{
  mpgrGroups[ibGroup].bSize = bSize;
}



nodes   GetGroupsNode(uchar  ibGroup, uchar  ibNode)
{
  return( mpgrGroups[ibGroup].mpnoNodes[ibNode] );
}


void    SetGroupsNode(uchar  ibGroup, uchar  ibNode, nodes  noT)
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

  cbUsedGroups = 0;
  for (i=0; i<bGROUPS; i++)
  {
    if (GetGroupsSize(i) != 0) 
    {
      mpboUsedGroups[i] = boTrue;
      cbUsedGroups++;
    }
    else
      mpboUsedGroups[i] = boFalse;
  }

  for (i=0; i<bCANALS; i++)
    mpboUsedNodes[i] = boFalse;            

  for (i=0; i<bGROUPS; i++)
  {
    for (j=0; j<GetGroupsSize(i); j++)
      mpboUsedNodes[ GetGroupsNodeCanal(i,j) ] = boTrue;
  }

  cbUsedNodes = 0;
  for (i=0; i<bCANALS; i++)
  {
    if (mpboUsedNodes[i] == boTrue)            
      cbUsedNodes++;      
  }
}



void    ResetGroups(void)
{
uchar   i;

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

  MakeUsedNodes();

  boSetGroups = boFalse;
}
