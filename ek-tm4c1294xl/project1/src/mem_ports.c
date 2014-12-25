/*------------------------------------------------------------------------------
MEM_PORTS.C


------------------------------------------------------------------------------*/

#include        "main.h"



// массив портов
port                    mppoPorts[bPORTS];

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
