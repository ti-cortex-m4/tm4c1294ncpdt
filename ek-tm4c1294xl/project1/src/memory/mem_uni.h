/*------------------------------------------------------------------------------
MEM_UNI.H


------------------------------------------------------------------------------*/

extern  uchar                   szObjectName[bNAME];

extern  uchar                   mpszCanalName[bCANALS][bNAME];

extern  uchar                   mpszGroupName[bGROUPS][bNAME];

extern  digital                 mpdiDevicesUni[bCANALS];

extern  uchar                   cbDevicesUni;

extern  uchar                   mpbDelayUni[bPORTS], mpbMaxDelayUni[bPORTS];

extern  uchar                   mpbGroupMaskUni[16];

extern  uchar                   mpbDefUni[64];

extern  boolean                 boStrictUni;
