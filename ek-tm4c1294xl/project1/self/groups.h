/*------------------------------------------------------------------------------
GROUPS.H


------------------------------------------------------------------------------*/

uchar   GetGroupsSize(uchar  ibGrp);
void    SetGroupsSize(uchar  ibGrp, uchar  bSize);

node    GetGroupsNode(uchar  ibGrp, uchar  ibNode);
void    SetGroupsNode(uchar  ibGrp, uchar  ibNode, node  nd);

bool    GetGroupsNodeSign(uchar  ibGrp, uchar  ibNode);
uchar   GetGroupsNodeCanal(uchar  ibGrp, uchar  ibNode);

void    MakeUsedNodes(void);

bool    SaveGroups(void);
bool    LoadGroups(void);

bool    IsValidGroup(group  *pgr);

void    ResetGroups(void);
void    InitGroups(void);
