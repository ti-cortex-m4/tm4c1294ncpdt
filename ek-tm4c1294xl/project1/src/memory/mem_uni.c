/*------------------------------------------------------------------------------
MEM_UNI.S


------------------------------------------------------------------------------*/

#include        "../main.h"



// имя объекта
uchar                   szObjectName[bNAME];

// имена каналов
uchar                   mpszCanalsName[bCANALS][bNAME];

// имена групп
uchar                   mpszGroupsName[bGROUPS][bNAME];

// устройства
digital                 mpdiDevicesUni[bCANALS];

// количество устройств
uchar                   cbDevicesUni;

// счетчик доступа к портам
uchar                   mpbDelayUni[bPORTS], mpbMaxDelayUni[bPORTS];

// маска групп
uchar                   mpbGroupMaskUni[16];

// маска брака
uchar                   mpbDefUni[64];

// признак строгого соблюдения протокола
boolean                 boStrictUni;
