/*------------------------------------------------------------------------------
MEM_FLOW.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// флаг включения транзита
bool                    fFlow;

// номер ведущего порта
uchar                   ibFlowPortFrom;

// номер ведомого порта
uchar                   ibFlowPortTo;

// счётчик таймаута транзита
uchar                   cbFlowDelay;

// таймаут транзита
uchar                   cbMaxFlowDelay;

// счётчик принятых байт
uint                    iwInFlow0, iwOutFlow0;

// счётчик количества приёмов
uchar                   cbInFlow0, cbOutFlow0;

// счётчик принятых байт
uint                    iwInFlow1, iwOutFlow1;

// счётчик количества приёмов
uchar                   cbInFlow1, cbOutFlow1;
