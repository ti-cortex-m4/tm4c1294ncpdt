/*------------------------------------------------------------------------------
GROUPS.C

 Группы
------------------------------------------------------------------------------*/

#include        "main.h"
#include        "mem_groups.h"
#include        "mem_program.h"
#include        "engine.h"
#include        "flash/files.h"



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

  for (i=0; i<bGROUPS; i++)
  {
    if (GetGroupsSize(i) != 0) 
      mpboUsedGroups[i] = boTrue;
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
}



void    ResetGroups(void)
{
uchar   i;
nodes   noT;

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


/*
bit     SaveGroups()
{
  OpenOut(wFLA_IMPMONCAN + ibMonTo*bIMPULSE);

  if (Save(mpimMonCanSpec, sizeof(impulse)*bCANALS) == 0)
    return(0);

  return( CloseOut() );
}


bit     LoadGroups(uchar  ibMonFrom)
{
  OpenIn(wFLA_IMPMONCAN + ibMonFrom*bIMPULSE);
  return( Load(mpimMonCanSpec, sizeof(impulse)*bCANALS) );
}
*/
