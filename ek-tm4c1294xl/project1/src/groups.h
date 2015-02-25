/*------------------------------------------------------------------------------
GROUPS.H

 Группы
------------------------------------------------------------------------------*/

uchar   GetGroupsSize(uchar  ibGroup);
void    SetGroupsSize(uchar  ibGroup, uchar  bSize);

node    GetGroupsNode(uchar  ibGroup, uchar  ibNode);
void    SetGroupsNode(uchar  ibGroup, uchar  ibNode, node  noT);

bool    GetGroupsNodeSign(uchar  ibGroup, uchar  ibNode);
uchar   GetGroupsNodeCanal(uchar  ibGroup, uchar  ibNode);

void    MakeUsedNodes(void);

void    ResetGroups(void);
void    InitGroups(void);
