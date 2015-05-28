/*------------------------------------------------------------------------------
MEM_PARAMS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// флаг разрешения опроса мгновенных параметров
bool                 boParamsFlag;

// флаг периода опроса мгновенных параметров (true: каждые 3 минуты, false: каждые 30 минут)
bool                 boMntParams;

// массив коэффициентов деления
real                    mpreParamsDiv[wPARAMS];

// массив разрешения опроса по параметрам
bool                 mpboEnblParams[wPARAMS];

// промежуточный массив
real                    mpreParamsBuff[2][wPARAMS];

// промежуточный массив
time                    mptiParamsBuff[wPARAMS];

// индекс по кольцевому буферу
uchar                   ibSoftTim;

// индекс по кольцевому буферу
uint                    iwHardTim;

// количество записей в журнале мгновенных параметров
uint                    cwParamTim;

// признак
bool                 boFixParamsBugs;

// признак
bool                 boUseParamsDiv;
