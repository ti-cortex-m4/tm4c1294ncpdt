/*------------------------------------------------------------------------------
MEM_UNI,S


------------------------------------------------------------------------------*/

#include "../main.h"



// название объекта
char                    szObjectName[bNAME_SIZE];

// названия каналов
char                    mpszCanalsName[bCANALS][bNAME_SIZE];

// названия групп
char                    mpszGroupsName[bGROUPS][bNAME_SIZE];

// массив устройств
digital                 mpdiDevicesUni[bCANALS];

// массив индексов первых каналов устройств
uchar                   mpibFirstCanalsUni[bCANALS];

// количество устройств
uchar                   cbDevicesUni;

// счетчики доступа к портам
uchar                   mpbDelayUni[bPORTS];

// максимальный счетчик доступа к портам
uchar                   bMaxDelayUni;

// маска групп
uchar                   mpbGroupMaskUni[16];

// маска брака
uchar                   mpbDefUni[64];

// признак строгого соблюдения протокола
bool                    boStrictUni;

// признак возобновления счетчика транзита после приема каждого байта
bool                    boRepeatFlowUni;

// признак необходимости использования пароля
bool                    boEnblPassUni;
