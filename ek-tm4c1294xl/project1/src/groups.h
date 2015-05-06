/*------------------------------------------------------------------------------
GROUPS.H

 ������
------------------------------------------------------------------------------*/

uchar   GetGroupsSize(uchar  ibGroup);
void    SetGroupsSize(uchar  ibGroup, uchar  bSize);

node    GetGroupsNode(uchar  ibGroup, uchar  ibNode);
void    SetGroupsNode(uchar  ibGroup, uchar  ibNode, node  noT);

bool    GetGroupsNodeSign(uchar  ibGroup, uchar  ibNode);
uchar   GetGroupsNodeCanal(uchar  ibGroup, uchar  ibNode);

void    MakeUsedNodes(void);

boolean SaveGroups(void);
boolean LoadGroups(void);

bool    TrueGroup(group  *pgr);

void    ResetGroups(void);
void    InitGroups(void);
