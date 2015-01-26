/*------------------------------------------------------------------------------
GROUPS.H

 ������
------------------------------------------------------------------------------*/

uchar   GetGroupsSize(uchar  ibGroup);
void    SetGroupsSize(uchar  ibGroup, uchar  bSize);

nodes   GetGroupsNode(uchar  ibGroup, uchar  ibNode);
void    SetGroupsNode(uchar  ibGroup, uchar  ibNode, nodes  noT);

bool    GetGroupsNodeSign(uchar  ibGroup, uchar  ibNode);
uchar   GetGroupsNodeCanal(uchar  ibGroup, uchar  ibNode);

void    MakeUsedNodes(void);

bool    SaveGroups(void);
bool    LoadGroups(void);

void    ResetGroups(void);
void    InitGroups(void);
