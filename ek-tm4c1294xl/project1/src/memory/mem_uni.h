/*------------------------------------------------------------------------------
MEM_UNI.H


------------------------------------------------------------------------------*/

extern  char                    szObjectName[bNAME];

extern  char                    mpszCanalsName[bCANALS][bNAME];

extern  char                    mpszGroupsName[bGROUPS][bNAME];

extern  digital                 mpdiDevicesUni[bCANALS];

extern  uchar                   cbDevicesUni;

extern  uchar                   mpbDelayUni[bPORTS], mpbMaxDelayUni[bPORTS];

extern  uchar                   mpbGroupMaskUni[16];

extern  uchar                   mpbDefUni[64];

extern  boolean                 boStrictUni;

extern  uchar                   bMaxDelayUni;

extern  boolean                 boRepeatFlowUni;
