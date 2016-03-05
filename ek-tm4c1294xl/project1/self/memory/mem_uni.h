/*------------------------------------------------------------------------------
MEM_UNI,H


------------------------------------------------------------------------------*/

extern  char                    szObjectName[bNAME_SIZE];

extern  char                    mpszCanalsName[bCANALS][bNAME_SIZE];

extern  char                    mpszGroupsName[bGROUPS][bNAME_SIZE];

extern  digital                 mpdiDevicesUni[bCANALS];

extern  uchar                   mpibFirstCanalsUni[bCANALS];

extern  uchar                   cbDevicesUni;

extern  uchar                   mpbDelayUni[bPORTS];

extern  uchar                   bMaxDelayUni;

extern  uchar                   mpbGroupMaskUni[16];

extern  uchar                   mpbDefUni[64];

extern  bool                    boStrictUni;

extern  bool                    boRepeatFlowUni;

extern  bool                    boEnblPassUni;
