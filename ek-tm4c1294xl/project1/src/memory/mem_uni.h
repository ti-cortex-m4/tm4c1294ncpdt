/*------------------------------------------------------------------------------
MEM_UNI.H


------------------------------------------------------------------------------*/

extern  uchar                   szObjectName[bNAME];

extern  uchar                   mpszCanalsName[bCANALS][bNAME];

extern  uchar                   mpszGroupsName[bGROUPS][bNAME];

extern  digital                 mpdiDevicesUni[bCANALS];

extern  uchar                   cbDevicesUni;

extern  uchar                   mpbDelayUni[bPORTS], mpbMaxDelayUni[bPORTS];

extern  uchar                   mpbGroupMaskUni[16];

extern  uchar                   mpbDefUni[64];

extern  boolean                 boStrictUni;

extern  uchar                   bMaxDelayUni;

extern  boolean                 boRepeatFlowUni;
