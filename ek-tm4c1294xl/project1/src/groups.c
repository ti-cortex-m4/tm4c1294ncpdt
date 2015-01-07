/*------------------------------------------------------------------------------
GROUPS.C

 Подпрограммы управления группами
------------------------------------------------------------------------------*/

#include        "main.h"
#include        "mem_groups.h"
#include        "mem_program.h"
#include        "engine.h"



// читает количества узлов в группе
uchar   GetGroupsSize(uchar  ibGroup)
{
  return( mpgrGroups[ibGroup].bSize );
}


// записывает количества узлов в группе
void    SetGroupsSize(uchar  ibGroup, uchar  bSize)
{
  mpgrGroups[ibGroup].bSize = bSize;
}



// читает узел из группы
nodes   GetGroupsNode(uchar  ibGroup, uchar  ibNode)
{
  return( mpgrGroups[ibGroup].mpnoNodes[ibNode] );
}


// записывает узел в группу
void    SetGroupsNode(uchar  ibGroup, uchar  ibNode, nodes  noT)
{
  mpgrGroups[ibGroup].mpnoNodes[ibNode] = noT;
}



// находит знак узла
bool    GetGroupsNodeSign(uchar  ibGroup, uchar  ibNode)
{
  return( (bool)(GetGroupsNode(ibGroup,ibNode).ibCanal & 0x80) );
}


// находит адрес узла
uchar   GetGroupsNodeCanal(uchar  ibGroup, uchar  ibNode)
{
  return( GetGroupsNode(ibGroup,ibNode).ibCanal & 0x7F );
}



// устанавливает флаги используемых узлов и групп
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



// устанавливает состояние групп по умолчанию
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


/*
bit     CheckGroupNeg(void)
{
uchar   i;

  for (i=0; i<GetGroupsSize(ibGrp); i++)
    if (GetGroupsNodeSign(ibGrp,i) == 1) return(1);

  return(0);
}


bit     CheckAllGroupsNeg(void)
{
  for (ibGrp=0; ibGrp<bGROUPS; ibGrp++)
    if (CheckGroupNeg() == 1) return(1);

  return(0);
}
*/
