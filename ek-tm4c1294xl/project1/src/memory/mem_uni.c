/*------------------------------------------------------------------------------
MEM_UNI.S


------------------------------------------------------------------------------*/

#include "../main.h"



// имя объекта
char                    szObjectName[bNAME_SIZE];

// имена каналов
char                    mpszCanalsName[bCANALS][bNAME_SIZE];

// имена групп
char                    mpszGroupsName[bGROUPS][bNAME_SIZE];

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
bool                    boStrictUni;

// максимальный счетчик
uchar                   bMaxDelayUni;

// флаг
bool                    boRepeatFlowUni;

// флаг
bool                    boEnblPassUni;
