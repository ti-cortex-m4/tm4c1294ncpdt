/*------------------------------------------------------------------------------
GROUPS.H

 Подпрограммы управления группами
------------------------------------------------------------------------------*/

#include        "main.h"



uchar   GetGroupsSize(uchar  ibGroup);
void    SetGroupsSize(uchar  ibGroup, uchar  bSize);

nodes   GetGroupsNode(uchar  ibGroup, uchar  ibNode);
void    SetGroupsNode(uchar  ibGroup, uchar  ibNode, nodes  noT);

bool    GetGroupsNodeSign(uchar  ibGroup, uchar  ibNode);
uchar   GetGroupsNodeCanal(uchar  ibGroup, uchar  ibNode);

void    MakeUsedNodes(void);
void    ResetGroups(void);

//bit     CheckGroupNeg(void);
//bit     CheckAllGroupsNeg(void);
