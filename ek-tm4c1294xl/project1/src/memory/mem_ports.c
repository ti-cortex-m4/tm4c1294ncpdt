/*------------------------------------------------------------------------------
MEM_PORTS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// массив портов
port                    mppoPorts[bPORTS];

// текущие счётчики таймаута на приём
uint                    mpwInDelay[bPORTS];

// начальные счётчики таймаута на приём (нормальные и расширенные)
uint                    mpwMinorInDelay[bPORTS], mpwMajorInDelay[bPORTS];

// массив временной смены режима портов
boolean                 mpboLocal[bPORTS];

// флаги запрещения временной смены режима
boolean                 mpboLocalDisable[bPORTS];

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
                        bInBuffA
                        bInBuffB,
                        bInBuffC,
                        bInBuffD,
                        bInBuffE,
                        bInBuffF;

// текущий запрос
uchar                   bQuery;

// анализируемый порт
uchar                   ibPortActive;
