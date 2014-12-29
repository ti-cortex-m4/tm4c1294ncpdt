/*------------------------------------------------------------------------------
MEM_PORTS.C


------------------------------------------------------------------------------*/

#include        "main.h"



// массив портов
port                    mppoPorts[bPORTS];

// флаг передачи 'AT'
boolean     			boSendAT;

// массив таймаутов передачи 'AT'
uchar                   mpcbSendAT[bPORTS];

// массив состояний передачи 'AT'
answer                  mpanSendAT[bPORTS];

// текущие счётчики таймаута на приём
uint                    mpwInDelay[bPORTS];

// начальные счётчики таймаута на приём (нормальные и расширенные)
uint                    mpwMinInDelay[bPORTS], mpwMajInDelay[bPORTS];

// массив временной смены режима портов
boolean                 mpboLocal[bPORTS];

// переменные
uchar                   bInBuff0,
                        bInBuff1,
                        bInBuff2,
                        bInBuff3,
                        bInBuff4,
                        bInBuff5,
                        bInBuff6,
                        bInBuff7,
                        bInBuff8,
                        bInBuff9,
                        bInBuffA;

// текущий запрос
uchar                   bQuery;

// анализируемый порт
uchar                   ibPortActive;
