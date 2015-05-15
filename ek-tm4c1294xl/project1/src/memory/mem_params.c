/*------------------------------------------------------------------------------
MEM_PARAMS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// флаг разрешения опроса мгновенных параметров
boolean                 boParamsFlag;

// флаг периода опроса мгновенных параметров (TRUE: каждые 3 минуты, FALSE: каждые 30 минут)
boolean                 boMntParams;

// массив коэффициентов деления
real                    mpreParamsDiv[wPARAMS];

// массив разрешения опроса по параметрам
boolean                 mpboEnblParams[wPARAMS];

// промежуточный массив
real                    mpreParBuff[2][wPARAMS];

// промежуточный массив
time                    mptiParBuff[wPARAMS];

// индекс по кольцевому буферу
uchar                   ibSoftTim;

// индекс по кольцевому буферу
uint                    iwHardTim;

// количество записей в журнале мгновенных параметров
uint                    cwParamTim;

// признак
boolean                 boFixParamsBugs;

// признак
boolean                 boUseParamsDiv;
